// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"

#include "SpiritCharacter.h"

ASpiritCharacter::ASpiritCharacter()
{
	for (uint8 i = 0; (ESpiritNature)i < ESpiritNature::MAX_ENUM; ++i)
		_spiritNatureParameter.Add((ESpiritNature)i);
}

void ASpiritCharacter::Init()
{
	Super::Init();
	_identity = Identity::Golem;

	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER;
		path += GetTypeAsFString() + GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
}

bool ASpiritCharacter::IsTimeDilated()
{
	return _isTimeDilated;
}

float ASpiritCharacter::GetSpecialSpiritRange()
{
	return _actionSpiritRange;
}

int ASpiritCharacter::GetSpiritRangeAttack(ESpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].rangeAttack;
}

int ASpiritCharacter::GetCurrentSpiritRangeAttack()
{
	return _spiritNatureParameter[_currentSpiritNature].rangeAttack;

}

int ASpiritCharacter::GetRangeAction(ESpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].rangeAction;

}

int ASpiritCharacter::GetCurrentRangeAction()
{
	return _spiritNatureParameter[_currentSpiritNature].rangeAction;

}

int ASpiritCharacter::GetEnergy(ESpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].currentEnergy;

}

int ASpiritCharacter::GetEnergyMax(ESpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].energyMax;

}

float ASpiritCharacter::GetTimeBetweenAction(ESpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].delayBetweenAction;
}

float ASpiritCharacter::GetCurrentTimeBetweenAction()
{
	return _spiritNatureParameter[_currentSpiritNature].energyMax;
}

float ASpiritCharacter::GetTimeSlowed(ESpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].timeSlowed;
}

float ASpiritCharacter::GetCurrentTimeSlowed()
{
	return _spiritNatureParameter[_currentSpiritNature].timeSlowed;

}

ESpiritNature ASpiritCharacter::GetCurrentSpiritNature()
{
	return _currentSpiritNature;
}

UParticleSystemComponent * ASpiritCharacter::GetParticuleActionRange()
{
	return _particuleActionRange;
}

void ASpiritCharacter::SetTimeDilated(bool isTimeSlowed)
{
	_isTimeDilated = isTimeSlowed;
}

void ASpiritCharacter::SetParticuleActionRange(UParticleSystemComponent * particule)
{
	_particuleActionRange = particule;
}

