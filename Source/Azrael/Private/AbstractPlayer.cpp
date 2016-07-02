// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AzraelSaver.h"
#include "PaperFlipbookComponent.h"
#include "SpiritCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbstractPlayer.h"

#define SCREEN(x) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,FString::Printf(TEXT("~> %f"), x))
#define SCREENCOL(x,col) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::##col,FString::Printf(TEXT(" ~> %f"), x))



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
	InputComponent->BindAction("SpiritAttack", IE_Pressed,  this,  &AAbstractPlayer::SpiritSight);
	InputComponent->BindAction("SpiritAttack", IE_Released, this,  &AAbstractPlayer::StopSpiritSight);
	


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
	InputComponent->BindAction("Anchor", IE_Pressed, this, &AAbstractPlayer::ExecAction);
	InputComponent->BindAction("Anchor", IE_Released, this, &AAbstractPlayer::ResetAction);

	InputComponent->BindAction("Sights", IE_Pressed, this, &AAbstractPlayer::EnablingSights);
	InputComponent->BindAction("Sights", IE_Released, this, &AAbstractPlayer::DisablingSights);


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

void AAbstractPlayer::SpiritSight()
{
	_spiritCharacter->SetTimeDilated(true);
	SpiritRangeParticle();

	// Dilate the Time for all actors but spirit
	TArray<AActor*> arrayOfActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), arrayOfActor);

	//Dilating the time for all actors
	for (int i = 0; i < arrayOfActor.Num(); i++)
		arrayOfActor[i]->CustomTimeDilation = .1f;
	//except the time dilation of the spirit
	_spiritCharacter->CustomTimeDilation = 1.0f;
} 

void AAbstractPlayer::StopSpiritSight()
{
	_spiritCharacter->SetTimeDilated(false);

	TArray<AActor*> arrayOfActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), arrayOfActor);
	//Dilating the time for all actors
	for (int i = 0; i < arrayOfActor.Num(); i++)
		arrayOfActor[i]->CustomTimeDilation = 1.f;
	
	if (_spiritCharacter->GetParticuleActionRange() && !_spiritCharacter->GetParticuleActionRange()->IsPendingKill())
		_spiritCharacter->GetParticuleActionRange()->DestroyComponent();
}

void AAbstractPlayer::SpiritRangeParticle()
{
	
	float spiritRange = _spiritCharacter->GetRangeAttack() * 0.87;

	_spiritCharacter->SetParticuleActionRange(UGameplayStatics::SpawnEmitterAttached(
							LoadParticle("/Game/Azrael/Gameplay/Content/Blueprint/SpiritBlue/Particle/SpiritRange.SpiritRange"),
							_spiritCharacter->GetSprite()));

	_spiritCharacter->GetParticuleActionRange()->SetFloatParameter("SpiritRange", spiritRange );

	GetWorldTimerManager().SetTimer(_countdownTimerHandle, this,
			&AAbstractPlayer::StopSpiritSight, _spiritCharacter->GetCurrentTimeSlowed(), false);
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
	if(!IsPawnJumping() && !_spiritCharacter->IsTimeDilated())
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

	if (_spiritCharacter->IsTimeDilated())
		MakeCircleTrigo();
}

void AAbstractPlayer::SpiritY(float value)
{
	_angleSpiritSinus = value;
	if (_spiritCharacter->IsTimeDilated())
		MakeCircleTrigo();
}

void AAbstractPlayer::ExecAction()
{
	if (!_spiritCharacter->IsTimeDilated())
		return;

	switch (_spiritCharacter->GetCurrentSpiritNature())
	{
	case ESpiritNature::Red :
		ExplodeAction();
		break;
	case ESpiritNature::Blue :
		AnchorAction();
		break;
	case ESpiritNature::Green:
		TranspositionAction();
		break;
	case ESpiritNature::Black:
		FreezeAction();
		break;
	default:
		break;
	}
}

void AAbstractPlayer::ResetAction()
{

}

void AAbstractPlayer::AnchorAction_Implementation()
{
	FHitResult OutHits;
	FVector begin = _spiritCharacter->GetActorLocation();

	float time = 0.5f;
	float x = _spiritCharacter->GetRangeAttack() * cos(UKismetMathLibrary::DegreesToRadians(_angleSpirit));
	float z = _spiritCharacter->GetRangeAttack() * sin(UKismetMathLibrary::DegreesToRadians(_angleSpirit));



	TArray<AActor*> anchors;
	TArray<AAnchor*> anchorsInRange ;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnchor::StaticClass(), anchors);
	for (int i = 0; i < anchors.Num(); ++i)
	{
		if (_spiritCharacter->GetDistanceTo(anchors[i]) < _spiritCharacter->GetRangeAction(ESpiritNature::Blue)
			&& _spiritCharacter->GetDistanceTo(anchors[i]) > 150.0f)
			anchorsInRange.Add(Cast<AAnchor>(anchors[i]));
	}

	if (anchorsInRange.Num() == 0) return;

	if (anchorsInRange.Num() == 1)
		_anchorSelected = Cast<AAnchor>(anchorsInRange[0]);
	else
	{
		int min = 0;
		for (int i = 0; i < anchorsInRange.Num()-1; ++i)
		{
			FVector spiritToAnchor = anchorsInRange[min]->GetActorLocation() - begin;
			FVector spiritToAnchorLast = anchorsInRange[i+1]->GetActorLocation() - begin;

			float FirstAngle  = (UFunctionLibrary::AngleBetweenVector(spiritToAnchor,FVector::ForwardVector));
			float SecondAngle = (UFunctionLibrary::AngleBetweenVector(spiritToAnchorLast, FVector::ForwardVector));
			if(abs(FirstAngle - _angleSpirit) > abs(SecondAngle - _angleSpirit))
				min = i+1;
			SCREEN(abs(FirstAngle - _angleSpirit));
			SCREENCOL(abs(SecondAngle - _angleSpirit), Blue);
			SCREENCOL(_angleSpirit, Green);

		}
		_anchorSelected = Cast<AAnchor>(anchorsInRange[min]);

	}

	if(_anchorSelected)
	{
		_angleSpirit = UFunctionLibrary::AngleBetweenVector(_anchorSelected->GetActorLocation()-_spiritCharacter->GetActorLocation(),
															FVector::ForwardVector);
		FVector end = _anchorSelected->GetActorLocation();
		bool hit = UKismetSystemLibrary::LineTraceSingle_NEW(GetWorld(),
			begin,
			end,
			ETraceTypeQuery::TraceTypeQuery1,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::Type::ForDuration,
			OutHits,
			true);

		if (Cast<AAnchor>(OutHits.GetActor()))
			GrappleLanch();

		if (_anchorSelected)
			StopSpiritSight();
	}
}

void AAbstractPlayer::ExplodeAction_Implementation()
{

}

void AAbstractPlayer::FreezeAction_Implementation()
{

}

void AAbstractPlayer::TranspositionAction_Implementation()
{

}

int AAbstractPlayer::GetSpiritEnergy(ESpiritNature spiritNature)
{
	return _spiritCharacter->GetEnergy(spiritNature);
}

int AAbstractPlayer::GetSpiritEnergyMax(ESpiritNature spiritNature)
{
	return _spiritCharacter->GetEnergyMax(spiritNature);
}

void AAbstractPlayer::MakeCircleTrigo()
{
	_angleSpirit = UKismetMathLibrary::DegAtan((_angleSpiritSinus / _angleSpiritCosinus));


	if (_angleSpiritCosinus <= 0)
	{
		if (_angleSpiritCosinus == 0.0f)
		{
			if (_angleSpiritSinus == -1.0f)
			{
				_angleSpirit = 270;
				return;
			}
			if (_angleSpiritSinus==0.0f)
			{
				_angleSpirit = 0.0f;
				return;
			}
		}
		if (_angleSpiritSinus >= 0)
		{
			if (_angleSpiritSinus == 0.f)
			{
				_angleSpirit = 180.0;
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

void AAbstractPlayer::ResetAnchor()
{
	//_anchorSelected = nullptr;
}

void AAbstractPlayer::GrappleLanch_Implementation()
{
	if (!_anchorSelected || _grapple)
		return;
}

void AAbstractPlayer::EnablingSights()
{
	if(_spiritCharacter->IsTimeDilated())
		_isSightsEnable = true;
}

void AAbstractPlayer::DisablingSights()
{
	_isSightsEnable = false;
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