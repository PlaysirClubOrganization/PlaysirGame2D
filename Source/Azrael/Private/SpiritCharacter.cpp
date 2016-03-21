// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "SpiritCharacter.h"




void ASpiritCharacter::Init()
{
	Super::Init();
	_identity = Identity::Golem;

	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER;
		path += GetTypeAsFString() + GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
}
