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
	UpdateAnimation();
}

void AAzraelCharacter::UpdateAnimation()
{
	//if Life is less than 0 the Ai is dying
	//else we check if the velocity of the AI is null
	float speed = GetVelocity().SizeSquared();

	if(_isAppearing)
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Appear_Animation));
	else if (_isAttacking)
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Attack_Animation));
	else if (_isDead)
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

void AAzraelCharacter::Init()
{
}

void AAzraelCharacter::Attack_Implementation()
{

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
	_currentAnim = Flipbook;
}

UPaperFlipbook * AAzraelCharacter::GetCurrentSprite()
{
	_currentAnim = GetSprite()->GetFlipbook();
	return _currentAnim;
}

int AAzraelCharacter::GetLife()
{
	return _life;
}

std::string AAzraelCharacter::GetType()
{
	switch (GetIdentity())
	{
	case Identity::Zombie:
		return std::string("Zombie/Flipbook/");
	case Identity::Vampire:
		return std::string("Vampire/Flipbook/");
	case Identity::Golem:
		return std::string("Golem/Flipbook/");
	default:
		return "Zombie/Flipbook/";
	}
}

Identity AAzraelCharacter::GetIdentity()
{
	return _identity;
}

/************************************************************************/
/*	Function for concat wchar_t and string                              */
/************************************************************************/
wchar_t * AAzraelCharacter::StrCncatCharW(wchar_t * dst, std::string src)
{
	//Getting the lenght of the wchar_t
	int n= wcslen(dst);
	
	//Allocate the precise size for the final wchar_t
	wchar_t * d = (wchar_t *)malloc(sizeof(wchar_t) * (1 + n + src.size()));
	
	// make the affectation d = dst we cannot concat dst with str directly 
	// because of the precise memory that we need also we will have some 
	// Chinese and Arabic and Mesopotamians letter in our result 
	for (int i = 0; i < n; ++i)
	{
		d[i] = dst[i];
	}
	//Now we append the src
	for (int i = 0; i < src.size(); ++i)
	{
		d[n + i] = src[i];
	}
	//We finish a wchar_t t with the \0 character
	d[n + src.size()] = L'\0';
	return d;
}

