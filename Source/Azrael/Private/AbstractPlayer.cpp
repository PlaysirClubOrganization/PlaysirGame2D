// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AbstractPlayer.h"

void AAbstractPlayer::Init()
{
	Super::Init();
	_identity = Identity::Skeleton;
	_life = 50;
	
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER;
		path += GetTypeAsFString() + GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
}


void AAbstractPlayer::AddCoin()
{
	_coin++;
}

void AAbstractPlayer::SaveData(UAzraelSaver * saver)
{
	saver->life = _life;
	saver->count = _coin;
	saver->level = ++_level;

}

void AAbstractPlayer::LoadData(UAzraelSaver * saver)
{
 	_life = saver->life;
	_coin = saver->count;
	_level = saver->level;
}
