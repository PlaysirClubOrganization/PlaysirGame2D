// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AzraelCharacter.h"
#include "SpiritCharacter.generated.h"



/** Defines the different SpiritNature */
UENUM(BlueprintType)
enum class SpiritNature: uint8
{
	Red,
	Blue,
	Green,
	Yellow
};

/**
 * 
 */
UCLASS()
class AZRAEL_API ASpiritCharacter : public AAzraelCharacter
{
	GENERATED_BODY()
public:

	virtual void Init();

	float GetTimeMastering();
	
	void IsTimeDilated(bool btimeDilated);

	bool IsMasteringTime();

	float GetSpecialSpiritRange();

	SpiritNature GetSpiritNature();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spirit)
	float _specialSpiritRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spirit)
	float _delayMasterOfTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spirit)
	uint32 _canAttack:1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spirit)
	uint32 _masteringTime: 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spirit)
	SpiritNature _spiritNature;

};
