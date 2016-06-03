// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AzraelSaver.h"
#include "PaperFlipbookComponent.h"
#include "SpiritCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbstractPlayer.h"

void AAbstractPlayer::Init()
{
	//Init the attribute of the player
	Super::Init();
	_identity = Identity::Skeleton;
	_life = 50;
	_endurance = 5.0f;
	_wallJumpPerf = .7f;
	
	//Load the animation paperFlipbook
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER;
		path += GetTypeAsFString() + GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
}


//unused :  for test
void AAbstractPlayer::AddCoin()
{
	_coin++;
}

void AAbstractPlayer::SaveData(UAzraelSaver * saver)
{
	//save all the attribute in the saver
	saver->life = _life;
	saver->count = _coin;
	saver->level = ++_level;
}

void AAbstractPlayer::LoadData(UAzraelSaver * saver)
{
	//load all the attribute from the saver
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
	InputComponent->BindAction("SpiritAttack", IE_Pressed,  this,  &AAbstractPlayer::TriggerTimeAttack);
	InputComponent->BindAction("SpiritAttack", IE_Released, this,  &AAbstractPlayer::StopAttack);
	
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
	InputComponent->BindAction("Dash", IE_Pressed, this, &AAbstractPlayer::Dash);


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AAbstractPlayer::EnablingCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AAbstractPlayer::DisablingCrouch);

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	InputComponent->BindAction("TriggerPilon", IE_Pressed, this, &AAbstractPlayer::EnablingPilon);
	InputComponent->BindAction("TriggerPilon", IE_Released, this, &AAbstractPlayer::DisablingPilon);
}

void AAbstractPlayer::Running()
{
	//Run button was pressed => enabling Run
	_canRun = true;
	//if the player is not sliding maxWalkspeed = runSpeed
	if (!IsSliding()) 
	{
		GetCharacterMovement()->MaxWalkSpeed = RUN_SPEED;
		SetRunning(true);
	}
	//The player cannot run more than its endurance
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
					&AAbstractPlayer::StopRunning, _endurance, false);

}


void AAbstractPlayer::StopRunning()
{
	_canRun = false;
	if (!(IsPawnJumping() || IsCrouching() || IsSliding()))
		GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	
	SetRunning(false);
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
}

void AAbstractPlayer::PlayerAttack()
{
	GetSprite()->SetPlayRate(1.0);	//speed of the animation sprite
	//if the player is not dead the player attacks and stop running
	if (!IsDead())
	{
		SetAttacking(true);
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
			&AAbstractPlayer::ResetAttack, GetCurrentSpriteLength(), false);
		SetRunning(false);
	}
}

void AAbstractPlayer::PlayerJump()
{
	//cannot jump while crouching
	if (IsCrouching()) return;

	_doubleJumpingTrigger++;
	/*******/
	if (_doubleJumpingTrigger == 1 && IsPawnJumping())
		WallJump();
	/*******/

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

void AAbstractPlayer::Dash()
{
	if (++_dashTrigger >= 2 || _spiritCharacter->IsAttacking())
	{
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
			&AAbstractPlayer::ResetDash, .5f, false);
		return ;
	}

	float boost = 5000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = boost * 4.f;
	GetCharacterMovement()->BrakingDecelerationWalking = boost * 4.f;
	GetCharacterMovement()->Velocity = FVector(-boost * GetPawnDirection(), 0.0f, 0.0f);

	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
		&AAbstractPlayer::ResetDash, .5f, false);

}

void AAbstractPlayer::ResetDash()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	_dashTrigger = 0;
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
		arrayOfActor[i]->CustomTimeDilation = .1f;
		
	_spiritCharacter->CustomTimeDilation = 1.0f;

	_spiritCharacter->SetAttacking(true);
}

void AAbstractPlayer::StopAttack()
{

	TArray<AActor*> arrayOfActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), arrayOfActor);

	for (int i = 0; i < arrayOfActor.Num(); i++)
		arrayOfActor[i]->CustomTimeDilation = 1.0f;

	_spiritCharacter->SetAttacking(false);
}

void AAbstractPlayer::WallJump()
{
	float z = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() - GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	FVector tmp   = FVector(0.0, 0.0, z);
	FVector Start = GetActorLocation() + tmp;
	FVector End	  = GetActorLocation() - tmp;
	FHitResult hitRes;


	bool hit = UKismetSystemLibrary::SphereTraceSingle_NEW(GetWorld(),
					Start,
					End,
					GetCapsuleComponent()->GetUnscaledCapsuleRadius() + 5.0f,
					ETraceTypeQuery::TraceTypeQuery1,
					false,
					TArray<AActor*>(),
					EDrawDebugTrace::Type::ForOneFrame,
					hitRes,
					true);

	if (hit && (int)hitRes.ImpactNormal.Z != 1)
	{
		tmp = UKismetMathLibrary::GreaterGreater_VectorRotator(hitRes.ImpactNormal,
											UKismetMathLibrary::SelectRotator( FRotator(0.0, 60.0, 0.0),
										 	FRotator(0.0, -60.0, 0.0),
											hitRes.ImpactNormal.X > 0.0));
		tmp = FVector(tmp.X*1500.0,0.0,1000.0 * _wallJumpPerf) - GetVelocity();
		LaunchCharacter(tmp, false, false);
		float yaw = UKismetMathLibrary::SelectFloat(0.0f, 180.0f, hitRes.ImpactNormal.X > 0.0);
		UKismetSystemLibrary::PrintString(GetWorld(), UKismetStringLibrary::Conv_VectorToString(hitRes.ImpactNormal));

		_doubleJumpingTrigger = 0;
		GetController()->SetControlRotation(FRotator(0.0, 0.0, yaw));
	}

}

void AAbstractPlayer::EnablingCrouch()
{
	if(!IsPawnJumping())_canCrouch = true;
}

void AAbstractPlayer::DisablingCrouch()
{
	_canCrouch = false;
	if(_isCrouching)
		CrouchAction(false);
}

void AAbstractPlayer::EnablingPilon()
{
	if (IsPawnJumping())
		_canPilon = true;
}

void AAbstractPlayer::DisablingPilon()
{
	_canPilon = false;
}

void AAbstractPlayer::CrouchAction(bool crouching)
{
	FHitResult hitRes;


	if (!crouching)
	{
		FVector End = GetActorLocation() + FVector(0.0, 0.0, HEIGHT / 4.5);
		bool hit = UKismetSystemLibrary::SphereTraceSingle_NEW(GetWorld(),
										GetActorLocation() + FVector(0.0, 0.0, 100.0),
										End,
										GetCapsuleComponent()->GetUnscaledCapsuleRadius() + RADIUS/5.0,
										ETraceTypeQuery::TraceTypeQuery1,
										false,
										TArray<AActor*>(),
										EDrawDebugTrace::Type::None,
										hitRes,
										true);
		if (hit)
			return;
		
		GetSprite()->SetRelativeLocation(FVector::ZeroVector, true, &hitRes, ETeleportType::TeleportPhysics);
		GetCapsuleComponent()->SetCapsuleSize(RADIUS, HEIGHT);
		GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
		SetCrouching(false);
		SetWalking(true);
	}
	else
	{
		GetSprite()->SetRelativeLocation(FVector(0.0, 0.0, 45.0), true, &hitRes, ETeleportType::TeleportPhysics);
		GetCapsuleComponent()->SetCapsuleSize(RADIUS, HEIGHT/2.0);
		GetCharacterMovement()->MaxWalkSpeed = CROUCH_SPEED;
		SetCrouching(true);
	}

}
