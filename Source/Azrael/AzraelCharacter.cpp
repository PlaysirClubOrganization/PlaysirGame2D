// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#include "Azrael.h"
#include "AzraelCharacter.h"
#include "PaperFlipbookComponent.h"



//////////////////////////////////////////////////////////////////////////
// AAzraelCharacter 
/////////////////////////////////////////////////////////////////////////


/************************************************************************/
/*  State Machine Manger  UpdateAnimation    &    UpdateCharacter       */
/************************************************************************/

void AAzraelCharacter::UpdateCharacter()
{
	if (GetVelocity().Z == 0.0)	//if the player has no velocity over the Z axis
		SetJumping(false);		// the player isn't jumping
	else
		SetJumping(true);		//else is jumping
	
	if (GetVelocity().X == 0.0)
		SetWalking(false);
	else
		SetWalking(true);

	UpdateAnimation();
}


void AAzraelCharacter::UpdateAnimation()
{
	//if Life is less than 0 the Ai is dying
	//else we check if the velocity of the AI is null
	float speed = GetVelocity().SizeSquared();


	if(IsAppearing())
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Appear_Animation));
	else if (IsAttacking())
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Attack_Animation));
	else if (IsDead())
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Dead_Animation));
	else if (IsCrouching())
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Crouch_Animation));
	else if (!speed)
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Idle_Animation));
	else if(IsPawnJumping())
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Jump_Animation));
	else if (IsSliding())
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Crouch_Animation));
	else
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Walk_Animation));
}

/********************************************************************************************************/
/*    Method :  - Init for initialisation						 										*
				  - Attack which manager the damages overrided in the subClasses						*
				  - Tick Called Every Frame																*
				  - GetCurrentSpriteLength return the time Lenght of the current Flipbook				*
				  - GetAnimationPaper return the Array which contains all the Flipbook					*
				  - GetFlipbook (id) return the flipbook associated with the id enum					*
				  - Get Current Sprite return the current sprite and update the parameter _currentSprite*
				  - GetLife return the life of the Pawn													*
				  - GetType return the associated string type with /Flipbook/ appended to the end		*
				  - GetIdentity return the Identity enum of the Pawn									*
*********************************************************************************************************/


int AAzraelCharacter::GetPawnDirection()
{
	return (int)(-2 * _lookAtRight) + 1;
}

void AAzraelCharacter::TurnPawnRotation()
{
	if (GetSprite()->GetRelativeTransform().GetRotation().Z < 0.1f)
	{
		GetSprite()->SetRelativeRotation(FRotator(0.0, 180.0f, 0.0f));
		_lookAtRight = true;
	}
	else
	{
		GetSprite()->SetRelativeRotation(FRotator(0.0, 0.0f, 0.0f));
		_lookAtRight = false;
	}
}

/* WARNING
	The subclass need to call the Init function to load the asset 
*/
void AAzraelCharacter::Init()
{
	//Init the m_animationArray which will contains all the Pawn'sFlipbooks
	_animationArray = new TArray<UPaperFlipbook *>();
}

void AAzraelCharacter::Attacking()
{
	GetSprite()->SetPlayRate(1.0f);
	if (_receiverAttack)
	{
		//Computing the direction of the player from the AI -1 if is at its left
		// 1 else
		int direction = (_receiverAttack->GetActorLocation().X < GetActorLocation().X) ? -1 : 1;
		//Compute the vector director between the Ai and the Player
		FVector directionBetweenPawn = _receiverAttack->GetActorLocation() - GetActorLocation();
		//Normalize the vector
		directionBetweenPawn.Normalize();
		//computing the cosine between the vector direction and the ForwardVector(1,0,0)
		float cos = abs(FVector::DotProduct(directionBetweenPawn, FVector::ForwardVector));
		//computing the sinus
		float sin = sqrt(1 - cos*cos);

		//if the Player is currently attacked we cannot attack twice in the same time
		if (!_receiverAttack->GetIsAttacked())
		{
			//if the player is in the Range Attack and if the AI is in attack mode and the life of
			//the Player is greater than 0
			if (GetDistanceTo(_receiverAttack) < GetRangeAttack() /*&& IsAttacking() */ && _receiverAttack->GetLife() >= 0)
			{
				//The target is Attacked
				_receiverAttack->SetAttacked(true);
				//TODO : Manager physic attack
				_receiverAttack->GetCharacterMovement()->Velocity = FVector(direction*GetForceAttack()*cos, 0.f, GetForceAttack()*sin);
				//Resetting the Timer
				GetWorldTimerManager().ClearTimer(_countdownTimerHandle);
				//The target receive the damage
				_receiverAttack->TakeDamages(GetPawnAttackDamages());
			}
		}
	}
	SetAttacking(false);
}

void AAzraelCharacter::Appear()
{	//The AI is appearing (necessary for playing the appear animation)
	SetAppearing(true);
	//New the Pawn Idles so we call the Idle function after that the appear animation ends
	GetWorldTimerManager().SetTimer(_countdownTimerHandle, this, &AAzraelCharacter::Idle, GetCurrentSpriteLength(), false);
}

void AAzraelCharacter::Idle()
{
	//Initialize the velocity, when the Pawn is Idle the velocity is null
	GetCharacterMovement()->StopMovementImmediately();
	//Set the right sprite
	//GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Idle_Animation));
	//the Pawn finish to appear
	SetAppearing(false);
}

void AAzraelCharacter::Dead()
{
	Destroy();
}


void AAzraelCharacter::TakeDamages(int damage)
{
	if (!_receiverAttack)
		return;
	_life -= damage;
	SetAttacked(false);
	if (_life <= 0) {
		if (IsDead()) {
			Destroy();
			return;
		}
		SetDead(true);
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Dead_Animation));
		GetWorldTimerManager().SetTimer(_countdownTimerHandle, this, &AAzraelCharacter::Dead, GetCurrentSpriteLength()-.1f, false);
	}
}



void AAzraelCharacter::BeginPlay()
{
	Super::BeginPlay();
	Init();
	//Let make the Panw appear
	Appear();
}

void AAzraelCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCharacter();
}


float AAzraelCharacter::GetCurrentSpriteLength()
{	
	return GetCurrentSprite()->GetTotalDuration();
}

TArray< UPaperFlipbook *> * AAzraelCharacter::GetAnimationPaper()
{
	return _animationArray;
}

UPaperFlipbook * AAzraelCharacter::GetFlipbook(AnimationState idAnim)
{
	return (*GetAnimationPaper())[idAnim];
}

void AAzraelCharacter::SetCurrentAnim(UPaperFlipbook * Flipbook)
{
	GetSprite()->SetFlipbook(Flipbook);
}

UPaperFlipbook * AAzraelCharacter::GetCurrentSprite()
{
	return GetSprite()->GetFlipbook();
}

int AAzraelCharacter::GetLife() const
{
	return _life;
}

void AAzraelCharacter::SetLife(int life)
{ 
	_life = life; 
}

bool AAzraelCharacter::IsDead() const
{
	return _isDead;
}

bool AAzraelCharacter::IsAppearing() const
{
	return _isAppearing;
}

bool AAzraelCharacter::IsWalking() const
{
	return _isWalking;
}

bool AAzraelCharacter::IsAttacked() const
{
	return _isAttacking;
}

bool AAzraelCharacter::IsAttacking() const
{
	return _isAttacking;
}

bool AAzraelCharacter::IsPawnJumping() const
{
	//return GetMovementComponent()->IsMovingOnGround();
	return _isJumping;
}

bool AAzraelCharacter::IsCrouching() const
{
	return _isCrouching;
}

bool AAzraelCharacter::IsSliding() const
{
	return _isSliding;
}

void AAzraelCharacter::SetJumping(bool isJumping)
{
	_isJumping = isJumping;
}

void AAzraelCharacter::SetAttacking(bool isAttacking)
{
	_isAttacking = isAttacking;
}

void AAzraelCharacter::SetAttacked(bool isAttacked)
{
	_isAttacked = isAttacked;
}

void AAzraelCharacter::SetWalking(bool isWalking)
{
	_isWalking = isWalking;
}

void AAzraelCharacter::SetAppearing(bool isAppearing)
{
	_isAppearing = isAppearing;
}

void AAzraelCharacter::SetCrouching(bool isCrouching)
{
	_isCrouching = isCrouching;

}

void AAzraelCharacter::SetSliding(bool isSliding)
{
	_isSliding = isSliding;

}

void AAzraelCharacter::SetDead(bool isDead)
{
	_isDead = isDead;
}

bool AAzraelCharacter::IsRunning()
{
	return _isRunning;
}

void AAzraelCharacter::SetRunning(bool isRunning)
{
	_isRunning = isRunning;
}

bool AAzraelCharacter::GetIsAttacked()
{
	return _isAttacked;
}

void AAzraelCharacter::SetIsAttacked(bool isAttacked)
{
	_isAttacked = isAttacked;
}

Identity AAzraelCharacter::GetIdentity()
{
	return _identity;
}

void AAzraelCharacter::Running()
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
	GetWorldTimerManager().SetTimer(_countdownTimerHandle, this,
		&AAzraelCharacter::StopRunning, _endurance, false);

}


void AAzraelCharacter::StopRunning()
{
	_canRun = false;
	if (!(IsPawnJumping() || IsCrouching() || IsSliding()))
		GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;

	SetRunning(false);
	GetWorldTimerManager().ClearTimer(_countdownTimerHandle);
}
/************************************************************************/
/* TODO                                                                 */
/************************************************************************/
float AAzraelCharacter::GetPawnAttackDamages()
{
	return 1.0f;
}


float AAzraelCharacter::GetRangeAttack()
{
	return 2000.0f;
}

float AAzraelCharacter::GetForceAttack()
{
	return _forceAttack;
}



std::string AAzraelCharacter::GetType()
{
	switch (GetIdentity())
	{
	case Identity::Zombie:
		return "Zombie/Flipbook/";
	case Identity::Vampire:
		return "Vampire/Flipbook/";
	case Identity::Golem:
		return "Golem/Flipbook/";
	case Identity::Skeleton:
		return "Skeleton/Flipbook/";
	default:
		return "Zombie/Flipbook/";
	}
}
FString AAzraelCharacter::GetTypeAsFString()
{
	switch (GetIdentity())
	{
	case Identity::Zombie:
		return "Zombie/Flipbook/";
	case Identity::Vampire:
		return "Vampire/Flipbook/";
	case Identity::Golem:
		return "Golem/Flipbook/";
	case Identity::Ghost:
		return "Ghost/Flipbook/";
	case Identity::Skeleton:
		return "Skeleton/Flipbook/";
	default:
		return "Zombie/Flipbook/";
	}
}

