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

void AAzraelCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
	case Identity_AI::Zombie:
		return std::string("Zombie/Flipbook/");
	case Identity_AI::Vampire:
		return "Vampire/Flipbook";
	default:
		return "Zombie/Flipbook/";
	}
}


Identity_AI AAzraelCharacter::GetIdentity()
{
	return _identity;
}




/************************************************************************/
/*	Function for concat wchar_t and string                              */
/************************************************************************/

wchar_t * AAzraelCharacter::StrCncatCharW(wchar_t * dst, std::string src, int n)
{
	wchar_t * d = (wchar_t *)malloc(sizeof(wchar_t) * (n + 1 + src.size()));
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

wchar_t * AAzraelCharacter::StrCncatCharW(wchar_t * dst, std::string src)
{
	int n = 35;
	wchar_t * d;
	d = (wchar_t *)malloc(sizeof(wchar_t) * (n + 1 + src.size()));
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

