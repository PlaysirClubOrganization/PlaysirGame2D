// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AzraelCharacter.h"
#include "SpiritCharacter.generated.h"





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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Energy)
	int _energyRed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Energy)
	int _MaxEnergyRed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Energy)
	int _energyBlue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Energy)
	int _MaxEnergyBlue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Energy)
	int _energyGreen;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Energy)
	int _MaxEnergyGreen;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Energy)
	int _energyYellow;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Energy)
	int _MaxEnergyYellow;
	
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
