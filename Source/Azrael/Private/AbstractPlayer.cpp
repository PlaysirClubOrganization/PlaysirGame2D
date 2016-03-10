// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AbstractPlayer.h"


AAbstractPlayer::AAbstractPlayer()
{
	_identity = Identity::Golem;
	_life = 19;
	//Transferring the Animation loaded in FConstructorStatics Struct into
	// the parameter m_animationMap
	m_animationArray = new TArray<UPaperFlipbook *>();
	FConstructorStatics ConstructorStatics(this);
	for (int i = 0; i < ConstructorStatics.AnimationInstance.Num(); ++i)
	{
		GetAnimationPaper()->Add(ConstructorStatics.AnimationInstance[i].Get());
	}
}

void AAbstractPlayer::UpdateAnimation()
{
	Super::UpdateAnimation();

}

void AAbstractPlayer::MoveRight(float Value)
{

}

void AAbstractPlayer::UpdateCharacter()
{
	Super::UpdateCharacter();
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
