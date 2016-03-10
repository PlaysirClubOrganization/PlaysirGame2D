// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Azrael.h"
#include "AzraelCharacter.h"



//////////////////////////////////////////////////////////////////////////
// AAzraelCharacter 

void AAzraelCharacter::Init()
{


}

void AAzraelCharacter::Attack_Implementation()
{

}

void AAzraelCharacter::UpdateAnimation()
{
	//if Life is less than 0 the Ai is dying
	//else we check if the velocity of the AI is null
	float speed = GetVelocity().SizeSquared();

	if (_isAttacking)
	{
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Attack_Animation));
	}
	else if (_isDead)
	{
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Dead_Animation));
	}
	else if (!speed)
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Idle_Animation));
	else
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Walk_Animation));
	//	else if(_isJumping)
	//	GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Jump_Animation));
}

void AAzraelCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCharacter();
}

void AAzraelCharacter::UpdateCharacter()
{
	UpdateAnimation();
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

	int n= wcslen(dst);

	wchar_t * d;
	d = (wchar_t *)malloc(sizeof(wchar_t) * (1 + n + src.size()));
	/* Find the end of dst and adjust bytes left but don't go past end */
	for (int i = 0; i < n; ++i)
	{
		d[i] = dst[i];
	}
	for (int i = 0; i < src.size(); ++i)
	{
		d[n + i] = src[i];
	}
	d[n + src.size()] = L'\0';
	return d;
}

