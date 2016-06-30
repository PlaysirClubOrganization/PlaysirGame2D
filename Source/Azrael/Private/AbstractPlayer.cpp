// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AzraelSaver.h"
#include "PaperFlipbookComponent.h"
#include "SpiritCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbstractPlayer.h"

#define SCREEN(x) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,FString::Printf(TEXT("~> %i"), x))
#define SCREENCOL(x,col) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::##col,FString::Printf(TEXT(" ~> %f"), x))

void AAbstractPlayer::Init()
{
	//Init the attribute of the player
	Super::Init();
	_identity = Identity::Skeleton;
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

void AAbstractPlayer::SaveData(UAzraelSaver * saver)
{
	//save all the attribute in the saver
	saver->life = _life;
	saver->level = ++_level;
}

void AAbstractPlayer::LoadData(UAzraelSaver * saver)
{
	//load all the attribute from the saver
 	_life = saver->life;
	_level = saver->level;
}
/************************************************************************/
/* Spirit Player Manager												*/
/************************************************************************/
void AAbstractPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	//AXIS BINDING

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	InputComponent->BindAxis("MoveRight", this, &AAbstractPlayer::MoveRight);

	InputComponent->BindAxis("SpiritX", this, &AAbstractPlayer::SpiritX);
	InputComponent->BindAxis("SpiritY", this, &AAbstractPlayer::SpiritY);


	//ACTION BINDING


	/************************************************************************/
	/* Spirit Attack : LT => trigger the dilatation of time                 */
	/************************************************************************/
	InputComponent->BindAction("SpiritAttack", IE_Pressed,  this,  &AAbstractPlayer::TriggerTimeAttack);
	InputComponent->BindAction("SpiritAttack", IE_Released, this,  &AAbstractPlayer::StopSpiritAttack);
	


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
	InputComponent->BindAction("Anchor", IE_Pressed, this, &AAbstractPlayer::Anchor);
	InputComponent->BindAction("Anchor", IE_Released, this, &AAbstractPlayer::ResetAnchorTarget);

}

void AAbstractPlayer::PlayerAttack()
{
	GetSprite()->SetPlayRate(1.0);	//speed of the animation sprite
	//if the player is not dead the player attacks and stop running
	if (!IsDead())
	{
		if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(EKeys::Gamepad_LeftStick_Down))
		{
			FHitResult OutHits;

			bool hit = UKismetSystemLibrary::LineTraceSingle_NEW(GetWorld(),
				GetActorLocation(),
				GetActorLocation() + FVector(0.0,0.0,-200.0),
				ETraceTypeQuery::TraceTypeQuery1,
				false,
				TArray<AActor*>(),
				EDrawDebugTrace::Type::ForDuration,
				OutHits,
				true);
			
			if (hit)
			{
				GetCharacterMovement()->Velocity.Z = -2500.0f;
				_isPiloning = true;
			}
		}

		SetRunning(false);
		SetAttacking(true);
		GetWorldTimerManager().SetTimer(_countdownTimerHandle, this,
			&AAbstractPlayer::ResetAttack, GetCurrentSpriteLength(), false);
	}
}

void AAbstractPlayer::PlayerJump()
{
	//cannot jump while crouching or dying or appearing or sliding
	if (IsCrouching() || IsDead() || IsAppearing() || IsSliding())
		return;

	//Check WallJump if the player is jumping and not in doubleJumping
	if (++_doubleJumpingTrigger == 1 && IsPawnJumping())
		WallJump();

	if (IsPawnJumping())
	{
		//Double Jumping if the doubleJumpTrigger equals to 1
		if (_doubleJumpingTrigger == 1)
		{
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			Jump();
		}
	}
	else
	{
		if (_dashTrigger)
			_dashTrigger = 0;

		//if the is the player is on the ground : he jumps normally
		Jump();
		//set the timer to reset the double jump trigger
		GetWorldTimerManager().SetTimer(_countdownTimerHandle, this,
			&AAbstractPlayer::ResetDoubleJumping, .07f, false);
	}

}

void AAbstractPlayer::Dash()
{
	if (!CanDash())
		return;
	else
	{
		float boost = 5000.0f;
		GetCharacterMovement()->BrakingDecelerationFalling = boost * 4.f;
		GetCharacterMovement()->BrakingDecelerationWalking = boost * 4.f;
		GetCharacterMovement()->Velocity = FVector(-boost * GetPawnDirection(), 0.0f, 0.0f);
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::Delay(GetWorld(), _dashDelay, LatentInfo);
	}
}

bool AAbstractPlayer::CanDash()
{
	return (++_dashTrigger < 2  &&  !_spiritCharacter->IsAttacking() && !IsCrouching());
}

void AAbstractPlayer::ResetDash()
{
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
	GetWorldTimerManager().ClearTimer(_countdownTimerHandle);
	_doubleJumpingTrigger= 0;
}

void AAbstractPlayer::ResetAttack()
{
	GetWorldTimerManager().ClearTimer(_countdownTimerHandle);
	SetAttacking(false);
}

void AAbstractPlayer::TriggerTimeAttack()
{
	SpiritRangeParticle();

	// Dilate the Time for all actors but spirit
	TArray<AActor*> arrayOfActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), arrayOfActor);

	//Dilating the time for all actors
	for (int i = 0; i < arrayOfActor.Num(); i++)
		arrayOfActor[i]->CustomTimeDilation = .1f;
	//except the time dilation of the spirit
	_spiritCharacter->CustomTimeDilation = 1.0f;
	
	_spiritCharacter->IsTimeDilated(true);
} 

void AAbstractPlayer::StopSpiritAttack()
{
	//_spiritCharacter->IsTimeDilated(false);
	
	TArray<AActor*> arrayOfActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), arrayOfActor);
	//Dilating the time for all actors
	for (int i = 0; i < arrayOfActor.Num(); i++)
		arrayOfActor[i]->CustomTimeDilation = 1.f;
	
	if (_spiritCharacter->_specialSpiritRange)
		_spiritCharacter->_specialSpiritRange->DestroyComponent();
}

void AAbstractPlayer::SpiritRangeParticle()
{
	
	float spiritRange = _spiritCharacter->GetRangeAttack() * 0.87;

	_spiritCharacter->_specialSpiritRange = (UGameplayStatics::SpawnEmitterAttached(
							LoadParticle("/Game/Azrael/Gameplay/Content/Particle/SpiritRange.SpiritRange"),
							_spiritCharacter->GetSprite()));
	_spiritCharacter->_specialSpiritRange->SetFloatParameter("SpiritRange", spiritRange );

	GetWorldTimerManager().SetTimer(_countdownTimerHandle, this,
			&AAbstractPlayer::StopSpiritAttack, _spiritCharacter->GetTimeMastering(), false);
}

void AAbstractPlayer::WallJump()
{
	float z = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() - GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	FVector tmp   = FVector(GetPawnDirection()*-30.0, 0.0, z/2.0);
	FVector Start = GetActorLocation() + tmp;
	FVector End	  = Start - FVector(0.0,0.0,z);
	FHitResult hitRes;

	bool hit = UKismetSystemLibrary::SphereTraceSingle_NEW(GetWorld(),
					Start,
					End,
					GetCapsuleComponent()->GetUnscaledCapsuleRadius() + 30.0f,
					ETraceTypeQuery::TraceTypeQuery1,
					false,
					TArray<AActor*>(),
					EDrawDebugTrace::Type::ForDuration,
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
	if(!IsPawnJumping() && !_spiritCharacter->IsMasteringTime())
		_canCrouch = true;
}

void AAbstractPlayer::DisablingCrouch()
{
	_canCrouch = false;
	if(_isCrouching)
		CrouchAction(false);
}

void AAbstractPlayer::EnablingPilon()
{
	if (IsPawnJumping() && ++_triggerPilon == 2)
	{
		_isPiloning = true;
		GetCharacterMovement()->Velocity = FVector(0.0, 0.0, -2500.0);
	}
	GetWorldTimerManager().SetTimer(_countdownTimerHandle, this,
		&AAbstractPlayer::ResetPilon, .3f, false);
	
}

void AAbstractPlayer::DisablingPilon()
{
	_isPiloning = false;
}

void AAbstractPlayer::ResetPilon()
{
	_triggerPilon = 0;
}

void AAbstractPlayer::SpiritX(float value)
{
	_angleSpiritCosinus = value;
}

void AAbstractPlayer::SpiritY(float value)
{
	_angleSpiritSinus = value;
}

void AAbstractPlayer::Anchor()
{
	if (_anchorMovement)
		return;
	float time = 0.5f;

	MakeCircleTrigo();
	_spiritCharacter->_masteringTime = true;
	if (_spiritCharacter->IsMasteringTime())
	{
		float x = _spiritCharacter->GetRangeAttack() * cos(UKismetMathLibrary::DegreesToRadians(_angleSpirit));
		float z = _spiritCharacter->GetRangeAttack() * sin(UKismetMathLibrary::DegreesToRadians(_angleSpirit));

		FHitResult OutHits;
		FVector end = _spiritCharacter->GetActorLocation() + FVector(x, 0.0, z);

		bool hit = UKismetSystemLibrary::SphereTraceSingle_NEW(GetWorld(),
											_spiritCharacter->GetActorLocation(),
											end,
											GetCapsuleComponent()->GetUnscaledCapsuleRadius() + RADIUS / 5.0,
											ETraceTypeQuery::TraceTypeQuery1,
											false,
											TArray<AActor*>(),
											EDrawDebugTrace::Type::ForDuration,
											OutHits,
											true);

		_anchorSelected = Cast<AAnchor>(OutHits.GetActor());
		GrappleLanch();

		if (_anchorSelected)
		{
			StopSpiritAttack();
		}
	}
	ResetAnchorTarget();
}

int AAbstractPlayer::GetSpiritEnergy(SpiritNature spiritNature)
{
	switch (spiritNature)
	{
	case SpiritNature::Red:
		return _spiritCharacter->_energyRed;
	case SpiritNature::Blue:
		return _spiritCharacter->_energyBlue;
	case SpiritNature::Green:
		return _spiritCharacter->_energyGreen;
	case SpiritNature::Yellow:
		return _spiritCharacter->_energyYellow;
	default:
		return 0;
	}
}

int AAbstractPlayer::GetSpiritEnergyMax(SpiritNature spiritNature)
{
	switch (spiritNature)
	{
	case SpiritNature::Red:
		return _spiritCharacter->_MaxEnergyRed;
	case SpiritNature::Blue:
		return _spiritCharacter->_MaxEnergyBlue;
	case SpiritNature::Green:
		return _spiritCharacter->_MaxEnergyGreen;
	case SpiritNature::Yellow:
		return _spiritCharacter->_MaxEnergyYellow;
	default:
		return 0;
	}
}

void AAbstractPlayer::MakeCircleTrigo()
{
	_angleSpirit = UKismetMathLibrary::DegAtan((_angleSpiritSinus / _angleSpiritCosinus));

	if (_angleSpiritCosinus <= 0)
	{
		if (_angleSpiritCosinus == 0.0f && _angleSpiritSinus == -1.0f)
		{
			_angleSpirit = 270;
			return;
		}
		if (_angleSpiritSinus >= 0)
		{
			if (_angleSpiritSinus == 0.f)
			{
				_angleSpirit = 180.0f;
				return;
			}
			else if (_angleSpirit != 90.f)
			{
				_angleSpirit = 180.0f + _angleSpirit;
				return;
			}
		}
		else
			_angleSpirit += 180.0f;
	}
	else
	{
		if (_angleSpiritSinus <= 0.0f)
			_angleSpirit = 360.0f + _angleSpirit;
	}
}

void AAbstractPlayer::ResetAnchorTarget()
{
	//_anchorSelected = nullptr;
}

void AAbstractPlayer::GrappleLanch_Implementation()
{
	int i = 0;
	//if (!_anchorSelected || _grapple)
		//return;
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

void AAbstractPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}