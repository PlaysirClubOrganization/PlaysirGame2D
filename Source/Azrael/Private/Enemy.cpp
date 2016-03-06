// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "TimerManager.h"
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
		FString myFString;
		if (enemy->GetIdentity().EndsWith("AI"))
			myFString = ("/Game/Azrael/Sprites/Enemy/" + enemy->GetIdentity());
		else
			myFString = "/Game/Azrael/Enemy/Zombie/Flipbook/appear.appear";

		const TCHAR *  t = *myFString;
		AnimationInstance.Add(ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>(TEXT("/Game/Azrael/Enemy/Zombie/Flipbook/appear.appear")));
		AnimationInstance.Add(ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>(TEXT("/Game/Azrael/Enemy/Zombie/Flipbook/idle.idle")));

	}
	~FConstructorStatics()
	{
	}

};

AEnemy::AEnemy()
{
	m_animationMap = new TArray<UPaperFlipbook *>();
	FConstructorStatics ConstructorStatics(this);
	for (uint8 i = 0; i < ConstructorStatics.AnimationInstance.Num();++i)
	{
		GetAnimationPaper()->Add(ConstructorStatics.AnimationInstance[i].Get());
	}


	_pawnSensing = (UPawnSensingComponent *)
		GetComponentByClass(UPawnSensingComponent::StaticClass());
}
AEnemy::~AEnemy()
{
	//for (uint8 i = 0; i < m_animationMap->Num();++i)
	//{
	//	delete (*m_animationMap)[i];
	//}
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
