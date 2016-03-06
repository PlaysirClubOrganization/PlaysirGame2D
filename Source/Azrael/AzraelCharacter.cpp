// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Azrael.h"
#include "AzraelCharacter.h"



//////////////////////////////////////////////////////////////////////////
// AAzraelCharacter 



void AAzraelCharacter::Init()
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
	return m_animationMap;
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

