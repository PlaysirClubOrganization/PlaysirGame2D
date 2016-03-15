// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AzraelSaver.h"
#include "AzraelCharacter.h"
#include "AbstractPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AZRAEL_API AAbstractPlayer : public AAzraelCharacter
{
	GENERATED_BODY()
protected:




public:
	
	AAbstractPlayer();

	virtual void Init();

	virtual bool	GetIsAttacked();

	virtual void	SetIsAttacked(bool isAttacked);
	
	UFUNCTION(BlueprintCallable, Category = Damage)
	virtual void	TakeDamages(int damage);


	virtual void	Dead();




protected:

};
