// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AbstractPlayer.h"
#include "EngineGlobals.h"


AAbstractPlayer::AAbstractPlayer()
{
	_identity = Identity::Player;
	_life = 19;
	Init();
}

void AAbstractPlayer::Init()
{
	Super::Init();
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = "/Game/Azrael/Enemy/";
		path += GetTypeAsFString() + GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
}



bool AAbstractPlayer::GetIsAttacked()
{
	return _isAttacked;
}

void AAbstractPlayer::SetIsAttacked(bool isAttacked)
{
	_isAttacked = isAttacked;
}

void AAbstractPlayer::TakeDamages(int damage)
{

	_life -= damage;
	if (_life <= 0) {
		_isDead = true;
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AAbstractPlayer::Dead, GetCurrentSpriteLength() - .1f , false);
	}
}

void AAbstractPlayer::Dead()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	Destroy();
}

