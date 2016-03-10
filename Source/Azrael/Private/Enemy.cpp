// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AzraelCharacter.h"
#include "TimerManager.h"
#include <iostream>
#include "Enemy.h"

/****************************************************************************/
/* Constructor of the AEnemy we choose not to make this class Abstract		*/
/* Because with Unreal API we must call the ContructorHelpers				*/
/* in the constructor. Thus making this class abstract wasn't a good choice */
/* for having a generic loader sprite										*/		
/****************************************************************************/
AEnemy::AEnemy()
{
	//Test for the Zombie (identity must be set before calling the FConstructorStatics
	_identity = Identity_AI::Zombie;


	//Transferring the Animation loaded in FConstructorStatics Struct into
	// the parameter m_animationMap
	m_animationArray = new TArray<UPaperFlipbook *>();
	FConstructorStatics ConstructorStatics(this);
	for (int i = 0; i < ConstructorStatics.AnimationInstance.Num();++i)
	{
		GetAnimationPaper()->Add(ConstructorStatics.AnimationInstance[i].Get());
	}
	_pawnSensing = (UPawnSensingComponent *)
		GetComponentByClass(UPawnSensingComponent::StaticClass());
}
//Amazing a Garbage Collector Exist so we doesn't Care of the destructor
AEnemy::~AEnemy()
{
}

void AEnemy::Appear()
{	//The AI is appearing (necessary for playing the appear animation)
	_isAppearing = true;
	//Setting the Appear Flipbook to the sprite
	GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Appear_Animation));
}


void AEnemy::UpdateAnimation()
{
	//if Life is less than 0 the Ai is dying
	//else we check if the velocity of the AI is null
	float speed = GetVelocity().SizeSquared();

	if (_isAttacking)
	{
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Attack_Animation));

	}
	else if (GetLife() <= 0)
	{
		Dead();
		return;
	}
	else if (!speed)
 		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Idle_Animation));
	else 
			GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Walk_Animation));
//	else if(_isJumping)
	//	GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Jump_Animation));
		

}

/*Unused for now*/
void AEnemy::MoveRight(float Value)
{

}
/*Unused for now*/
void AEnemy::UpdateCharacter()
{
	UpdateAnimation();

	APawn * Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (GetDistanceTo(Player) < 200.0f) {
		_isAttacking = true;
		auto t = GetWorldTimerManager().GetTimerRate(CountdownTimerHandle);
 		if ( t != TIME_FOR_ATTACK)
		{
			SetPlayerAttacked(true);
			GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AEnemy::Attack,TIME_FOR_ATTACK, false);
		}
		else
			SetPlayerAttacked(false);
	}
	else
	{
		SetPlayerAttacked(false);
		_isAttacking = false;

	}

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

void AEnemy::Patrol()
{
	if (GetTransform().GetRotation().Z < 0.1f)
	{
		SetActorRotation(FRotator(0.0, 180.0f, 0.0f));	
		_lookAtRight = true;
	}
	else
	{
		SetActorRotation(FRotator(0.0, 0.0f, 0.0f));
		_lookAtRight = false;
	}
		
}

void AEnemy::Attack_Implementation()
{
	AAbstractPlayer * Player = (AAbstractPlayer *)UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Player)
	{
		if (!Player->GetIsAttacked())
		{
			Player->GetCharacterMovement()->Velocity = FVector(GetDirection()*-1000.f, 0.f, 0.f);
			GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
			Player->TakeDamages(20);
		}
	}
}

int AEnemy::GetDirection()
{
	return (int)_lookAtRight * 2 - 1;
}

void AEnemy::SetPlayerAttacked(bool attack)
{
	AAbstractPlayer * Player = (AAbstractPlayer *)UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Player->SetIsAttacked(attack);
}













