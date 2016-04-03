// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AzraelSaver.h"
#include "PaperFlipbookComponent.h"
#include "SpiritCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbstractPlayer.h"

void AAbstractPlayer::Init()
{
	Super::Init();
	_identity = Identity::Skeleton;
	_life = 50;
	
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER;
		path += GetTypeAsFString() + GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
}



void AAbstractPlayer::AddCoin()
{
	_coin++;
}

void AAbstractPlayer::SaveData(UAzraelSaver * saver)
{
	saver->life = _life;
	saver->count = _coin;
	saver->level = ++_level;

}

void AAbstractPlayer::LoadData(UAzraelSaver * saver)
{
 	_life = saver->life;
	_coin = saver->count;
	_level = saver->level;
}
/************************************************************************/
/* Spirit Player Manager												*/
/************************************************************************/
void AAbstractPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	/************************************************************************/
	/* Spirit Attack : LT => trigger the dilatation of time                 */
	/************************************************************************/
	InputComponent->BindAction("SpiritAttack", IE_Pressed, this, &AAbstractPlayer::TriggerTimeAttack);
	InputComponent->BindAction("SpiritAttack", IE_Released, this, &AAbstractPlayer::StopAttack);
	
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	InputComponent->BindAxis("MoveRight", this, &AAbstractPlayer::MoveRight);

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	InputComponent->BindAction("Jump", IE_Pressed, this, &AAbstractPlayer::PlayerJump);

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	InputComponent->BindAction("PlayerAttack", IE_Pressed, this, &AAbstractPlayer::PlayerAttack);

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	InputComponent->BindAction("Run", IE_Pressed, this, &AAbstractPlayer::Running);
	InputComponent->BindAction("Run", IE_Released, this, &AAbstractPlayer::StopRunning);

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	InputComponent->BindAction("DashRight", IE_Pressed, this, &AAbstractPlayer::DashRight);
	InputComponent->BindAction("DashLeft", IE_Released, this, &AAbstractPlayer::DashLeft);
}

void AAbstractPlayer::Running()
{
	_canRun = true;
	GetCharacterMovement()->MaxWalkSpeed =  RUN_SPEED;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
		&AAbstractPlayer::StopRunning, _endurance, false);

}

void AAbstractPlayer::StopRunning()
{
	_canRun = false;
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
}

void AAbstractPlayer::PlayerAttack()
{
	GetSprite()->SetPlayRate(1.0);
	if (!IsDead())
	{
		SetAttacking(true);
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
			&AAbstractPlayer::ResetAttack, GetCurrentSpriteLength(), false);
	}
}



void AAbstractPlayer::PlayerJump()
{
	_doubleJumpingTrigger++;
	if (_canClimb)
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	if (IsPawnJumping())
	{
		if (_doubleJumpingTrigger == 1)
		{
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			Jump();
		}
	}
	else
	{
		Jump();
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
			&AAbstractPlayer::ResetDoubleJumping, .07f, false);
	}

}
void AAbstractPlayer::DashRight()
{
	if (GetCharacterMovement()->IsMovingOnGround())
		return;
	_doubleDashTriggerRight++;
	if (_doubleDashTriggerRight == 2)
		ExecDash();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
		&AAbstractPlayer::ResetDash, .3f, false);
}

void AAbstractPlayer::ExecDash()
{
	float boost = 5000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = boost * 4.f;
	GetCharacterMovement()->BrakingDecelerationWalking = boost * 4.f;
	GetCharacterMovement()->Velocity = FVector(-boost * GetPawnDirection(), 0.0f, 0.0f);
}

void AAbstractPlayer::DashLeft()
{
	if (GetCharacterMovement()->IsMovingOnGround())
		return;
	_doubleDashTriggerLeft++;
	if (_doubleDashTriggerLeft == 2)
		ExecDash();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
		&AAbstractPlayer::ResetDash, .3f, false);
}

void AAbstractPlayer::ResetDash()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	_doubleDashTriggerRight = 0;
	_doubleDashTriggerLeft = 0;
	GetCharacterMovement()->BrakingDecelerationFalling = BRAKING_DECELERATION_FALLING;
	GetCharacterMovement()->BrakingDecelerationWalking = BRAKING_DECELERATION_WALKING;
}


void AAbstractPlayer::MoveRight(float value)
{
	if (!IsAttacking()) {
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
		if ((GetPawnDirection() == -1 && value < 0.0f) ||
			(GetPawnDirection() == 1 && value > 0.0f))
			TurnPawnRotation();
	
		if (abs(value) > 0.55f) {
			if (_canRun)
				GetSprite()->SetPlayRate(2.0*abs(value));
			else
				GetSprite()->SetPlayRate(abs(value));
		}
	}
}


void AAbstractPlayer::ResetDoubleJumping()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	_doubleJumpingTrigger= 0;
}

void AAbstractPlayer::ResetAttack()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	SetAttacking(false);
}
void AAbstractPlayer::TriggerTimeAttack()
{
	TArray<AActor*> arrayOfActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), arrayOfActor);

	for ( int i = 0; i < arrayOfActor.Num();i++)
	{
		arrayOfActor[i]->CustomTimeDilation = .1f;
	}
//	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), .05f);
		_spiritCharacter->CustomTimeDilation = 1.0f;

	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
						&AAbstractPlayer::StopAttack, 2.0f, false);
	_spiritCharacter->SetAttacking(true);
}

void AAbstractPlayer::StopAttack()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	_spiritCharacter->SetAttacking(false);

	TArray<AActor*> arrayOfActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), arrayOfActor);

	for (int i = 0; i < arrayOfActor.Num(); i++)
	{
		arrayOfActor[i]->CustomTimeDilation = 1.0f;
	}
}


