// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AzraelCharacter.h"
#include "TimerManager.h"
#include "Enemy.h"


/****************************************************************************/
/* Constructor of the AEnemy we choose not to make this class Abstract		*/
/* Because with Unreal API we must call the ContructorHelpers				*/
/* in the constructor. Thus making this class abstract wasn't a good choice */
/* for having a generic loader sprite										*/		
/****************************************************************************/
//AEnemy::AEnemy()
//{
	//m_animationArray = new TArray<UPaperFlipbook *>();
	//Transferring the Animation loaded in FConstructorStatics Struct into
	// the parameter m_animationMap
	//FConstructorStatics ConstructorStatics(this);
	//for (int i = 0; i < ConstructorStatics.AnimationInstance.Num(); ++i)
	//{
	//	GetAnimationPaper()->Add(ConstructorStatics.AnimationInstance[i].Get());
	//}
	//_pawnSensing = (UPawnSensingComponent *)
	//GetComponentByClass(UPawnSensingComponent::StaticClass());
//}

void AEnemy::Init()
{
	Super::Init();
	//Transferring the Animation loaded in FConstructorStatics Struct into
	// the parameter m_animationMap
		
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER ;
		path += GetTypeAsFString()+ GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
	_pawnSensing = (UPawnSensingComponent *)
		GetComponentByClass(UPawnSensingComponent::StaticClass());
}

/*Unused for now*/
void AEnemy::UpdateCharacter()
{
	Super::UpdateCharacter();
	
	AAbstractPlayer * Player = GetPlayer();
	if (Player)

		if (GetDistanceTo(Player) < 180.0f && !IsAttacking() && !IsPawnJumping()) {
			SetAttacking(true);
			auto timer = GetWorldTimerManager().GetTimerRate(CountdownTimerHandle);
			if (timer != GetFlipbook(Attack_Animation)->GetTotalDuration())
			{
				GetCharacterMovement()->StopMovementImmediately();
				SetPlayerAttacked(true);
				GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AEnemy::Attack, GetFlipbook(Attack_Animation)->GetTotalDuration()/2.0, false);
			}
		}
		else {
			SetPlayerAttacked(false);
		}
		if (IsPawnJumping())
			GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		else if (_isPatrolling && !_isImmobile) {
			GetCharacterMovement()->Velocity = FVector(GetDirection()*-100.f, 0.f, 0.f);
		}
}


void AEnemy::Patrol()
{
	SetAppearing(false);
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
	AAbstractPlayer * Player = GetPlayer();
	if (Player)
	{
		if (!Player->GetIsAttacked())
		{
			if (GetDistanceTo(Player) < GetRangeAttack() && IsAttacking() && Player->GetLife()>=0)
			{
				Player->GetCharacterMovement()->Velocity = FVector(GetDirection()*-1000.f, 0.f, 0.f);
				GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
				Player->TakeDamages(20);
			}
		}
	}
	_isAttacking = false;
}

int AEnemy::GetDirection()
{
	return (int)_lookAtRight * 2 - 1;
}

float AEnemy::GetRangeAttack()
{
	return _rangeAttack;
}


void AEnemy::SetPlayerAttacked(bool attack)
{
	AAbstractPlayer * Player = GetPlayer();
	Player->SetIsAttacked(attack);
}