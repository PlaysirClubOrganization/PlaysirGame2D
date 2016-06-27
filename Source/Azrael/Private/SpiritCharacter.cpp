// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "SpiritCharacter.h"

void ASpiritCharacter::Init()
{
	Super::Init();
	_identity = Identity::Golem;
	_delayMasterOfTime =  2.70f;

	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER;
		path += GetTypeAsFString() + GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
}

float ASpiritCharacter::GetTimeMastering()
{
	return (_delayMasterOfTime > 0.f) ? _delayMasterOfTime : .12f; 
}

void ASpiritCharacter::IsTimeDilated(bool btimeDilated)
{
	_masteringTime = btimeDilated;
}
bool ASpiritCharacter::IsMasteringTime()
{
	return _masteringTime;
}

float ASpiritCharacter::GetSpecialSpiritRange()
{
	return _specialSpiritRange;
}

SpiritNature ASpiritCharacter::GetSpiritNature()
{
	return _spiritNature;
}

