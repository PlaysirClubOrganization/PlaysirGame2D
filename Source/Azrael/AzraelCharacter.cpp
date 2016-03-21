// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Azrael.h"
#include "AzraelCharacter.h"



//////////////////////////////////////////////////////////////////////////
// AAzraelCharacter 
/////////////////////////////////////////////////////////////////////////


/************************************************************************/
/*  State Machine Manger  UpdateAnimation    &    UpdateCharacter       */
/************************************************************************/

void AAzraelCharacter::UpdateCharacter()
{
	if (GetVelocity().Z == 0.0)
		SetJumping(false);
	else
		SetJumping(true);
	
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
	else if (!speed)
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Idle_Animation));
	else
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Walk_Animation));
	//	else if(_isJumping)
	//	GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Jump_Animation));
}

/********************************************************************************************************/
/*    Function :  - Init for initialisation (not used for now)											*
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


/* WARNING
	The subclass need to call the Init function to load the asset 
*/


void AAzraelCharacter::Init()
{
	//Init the m_animationArray which will contains all the Pawn'sFlipbooks
	m_animationArray = new TArray<UPaperFlipbook *>();
}

void AAzraelCharacter::Appear()
{	//The AI is appearing (necessary for playing the appear animation)
	SetAppearing(true);
	//New the Pawn Idles so we call the Idle function after that the appear animation ends
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AAzraelCharacter::Idle, GetCurrentSpriteLength(), false);
}

void AAzraelCharacter::Idle()
{
	//the Pawn finish to appear
	SetAppearing(false);
	//Inialize the velocity, when the Panw is Idle the velocity is null
	GetCharacterMovement()->StopMovementImmediately();
	//Set the right sprite
	GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Idle_Animation));
}

void AAzraelCharacter::Attack_Implementation()
{

}

void AAzraelCharacter::Dead()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	Destroy();
}


void AAzraelCharacter::TakeDamages(int damage, AAzraelCharacter * enemy)
{
	_life -= damage;
	SetAppearing(false);
	SetAttacked(false);
	if (_life <= 0) {
		SetDead(true);
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Dead_Animation));
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AAzraelCharacter::Dead, GetCurrentSpriteLength()-.1f, false);
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
	return m_animationArray;
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
	return _isJumping;
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

void AAzraelCharacter::SetDead(bool isDead)
{
	_isDead = isDead;
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

Identity AAzraelCharacter::GetIdentity()
{
	return _identity;
}

