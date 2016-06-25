// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "SpiritCharacter.h"

void ASpiritCharacter::Init()
{
	Super::Init();
	
	_rangeAttack = 300.f;
	_identity = Identity::Golem;
	_delayForAttack =  2.70f;


	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER;
		path += GetTypeAsFString() + GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
}

float ASpiritCharacter::GetTimeDelayForAttack()
{
	return (_delayForAttack > 0.f) ? _delayForAttack : .12f; 
}

