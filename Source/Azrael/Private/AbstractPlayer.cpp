// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AbstractPlayer.h"


AAbstractPlayer::AAbstractPlayer()
{

}

void AAbstractPlayer::UpdateAnimation()
{

}

void AAbstractPlayer::MoveRight(float Value)
{

}

void AAbstractPlayer::UpdateCharacter()
{
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
		GetSprite()->SetFlipbook(GetFlipbook(AnimationState::Dead_Animation));
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AAbstractPlayer::Dead, GetCurrentSpriteLength(), false);
	}
}

void AAbstractPlayer::Dead()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	Destroy();
}
