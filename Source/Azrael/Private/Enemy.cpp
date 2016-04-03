// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AzraelCharacter.h"
#include "AbstractPlayer.h"
#include "Perception/PawnSensingComponent.h"
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
	// Loading the PaperFlipbook animation
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER ;
		path += GetTypeAsFString()+ GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
	_pawnSensing = (UPawnSensingComponent *)
		GetComponentByClass(UPawnSensingComponent::StaticClass());
	receiverAttack = GetPlayer();
}

/*Unused for now*/
void AEnemy::UpdateCharacter()
{
	Super::UpdateCharacter();
	
	if (receiverAttack)

		if (GetDistanceTo(receiverAttack) < GetRangeAttack() && !IsAttacking() && !receiverAttack->IsAttacked()) {
			auto timer = GetWorldTimerManager().GetTimerRate(CountdownTimerHandle);
			if (timer != GetFlipbook(Attack_Animation)->GetTotalDuration())
			{
				SetAttacking(true);
				GetCharacterMovement()->StopMovementImmediately();
				GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AAzraelCharacter::Attack, GetFlipbook(Attack_Animation)->GetTotalDuration()/2.0f, false);
			}
		}
		else {
			receiverAttack->SetAttacked(false);
		}
		if (IsPawnJumping())
			GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		else if (_isPatrolling && !_isImmobile) {
			GetCharacterMovement()->Velocity = FVector(GetPawnDirection()*-100.f, 0.f, 0.f);
		}
}

void AEnemy::Patrol()
{
	SetAppearing(false);
	TurnPawnRotation();
	
}


float AEnemy::GetRangeAttack()
{
	return _rangeAttack;
}

float AEnemy::GetPawnAttackDamages()
{
	return _pawnAttackDamages;
}
