// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "TimerManager.h"
#include <iostream>
#include "Enemy.h"


/*
* FConstructorStatics will automatically load the different sprite of the any character by giving
* the right id in the init function.
*
* @warning : The project must bu construct
*/
struct FConstructorStatics
{
	TArray<ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>> AnimationInstance;
	FConstructorStatics(AEnemy *enemy)
		: AnimationInstance(TArray<ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>>())
	{
		wchar_t *dst = (L"/Game/Azrael/Enemy/Zombie/Flipbook/\0");
		
		for (int i = 0; i < 6; i++)
		{
			wchar_t * d = enemy->StrCncatCharW(dst, GetAnimationName(i));
			AnimationInstance.Add(ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>(d));
		}

	}

	~FConstructorStatics()
	{
	}

};

AEnemy::AEnemy()
{
	m_animationMap = new TArray<UPaperFlipbook *>();
	FConstructorStatics ConstructorStatics(this);
	for (int i = 0; i < ConstructorStatics.AnimationInstance.Num();++i)
	{
		GetAnimationPaper()->Add(ConstructorStatics.AnimationInstance[i].Get());
	}


	_pawnSensing = (UPawnSensingComponent *)
		GetComponentByClass(UPawnSensingComponent::StaticClass());
}
AEnemy::~AEnemy()
{

}
void AEnemy::Appear()
{
	_isAppearing = true;
	GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Appear_Animation));
}

void AEnemy::UpdateAnimation()
{
	if (GetLife() <= 0) 
		Dead();
	else if (GetVelocity().IsZero() ||
			 GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling ||
		     GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Flying)
	
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Idle_Animation));
	else
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Walk_Animation));


		
}

void AEnemy::MoveRight(float Value)
{

}

void AEnemy::UpdateCharacter()
{

}

void AEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCharacter();
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
	Appear();

}

void AEnemy::Dead()
{
	GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Dead_Animation));
}

void AEnemy::Init()
{
	Super::Init();
}

void AEnemy::Idle()
{
	_isAppearing = false;
	GetCharacterMovement()->StopMovementImmediately();
	GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Idle_Animation));
}

wchar_t * AEnemy::StrCncatCharW(wchar_t * dst, std::string src)
{
	int n = 35;
	wchar_t * d;
	d = (wchar_t *)malloc(sizeof(wchar_t) * (n + src.size()));
	/* Find the end of dst and adjust bytes left but don't go past end */
	for (int i = 0; i < n; ++i)
	{
		d[i] = dst[i];
	}
	for (int i = 0; i < src.size(); ++i)
	{
		d[n + i] = src[i];
	}
	d[n + src.size()] = L'\0';
	return d;
}
