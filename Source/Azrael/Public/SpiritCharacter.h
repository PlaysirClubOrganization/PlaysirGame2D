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


	UFUNCTION(BlueprintCallable, Category = Attack)
	virtual void Attack();
	
	float GetTimeDelayForAttack();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float _radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float _delayForAttack;

};
