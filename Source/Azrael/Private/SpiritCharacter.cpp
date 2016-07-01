// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"

#include "SpiritCharacter.h"

ASpiritCharacter::ASpiritCharacter()
{
	for (uint8 i = 0; i < 4; ++i)
		_spiritNatureParameter.Add((SpiritNature)i);
}

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
	return _actionSpiritRange;
}

int ASpiritCharacter::GetSpiritRangeAttack(SpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].rangeAttack;
}

int ASpiritCharacter::GetCurrentSpiritRangeAttack()
{
	return _spiritNatureParameter[_currentSpiritNature].rangeAttack;

}

int ASpiritCharacter::GetRangeAction(SpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].rangeAction;

}

int ASpiritCharacter::GetCurrentRangeAction()
{
	return _spiritNatureParameter[_currentSpiritNature].rangeAction;

}

int ASpiritCharacter::GetEnergy(SpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].currentEnergy;

}

int ASpiritCharacter::GetEnergyMax(SpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].energyMax;

}

float ASpiritCharacter::GetTimeBetweenAction(SpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].delayBetweenAction;
}

float ASpiritCharacter::GetCurrentTimeBetweenAction()
{
	return _spiritNatureParameter[_currentSpiritNature].energyMax;
}

float ASpiritCharacter::GetTimeSlowed(SpiritNature spiritNature)
{
	return _spiritNatureParameter[spiritNature].timeSlowed;
}

float ASpiritCharacter::GetCurrentTimeSlowed()
{
	return _spiritNatureParameter[_currentSpiritNature].timeSlowed;

}

SpiritNature ASpiritCharacter::GetCurrentSpiritNature()
{
	return _currentSpiritNature;
}

UParticleSystemComponent * ASpiritCharacter::GetParticuleActionRange()
{
	return _particuleActionRange;
}

void ASpiritCharacter::SetMasteringTime(bool isTimeSlowed)
{
	_masteringTime = isTimeSlowed;
}

void ASpiritCharacter::SetParticuleActionRange(UParticleSystemComponent * particule)
{
	_particuleActionRange = particule;
}

