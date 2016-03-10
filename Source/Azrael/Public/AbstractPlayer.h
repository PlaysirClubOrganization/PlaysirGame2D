// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AzraelCharacter.h"
#include "AbstractPlayer.generated.h"

/**
 * 
 */
UCLASS(abstract)
class AZRAEL_API AAbstractPlayer : public AAzraelCharacter
{
	GENERATED_BODY()
	
public:
	
	virtual void	UpdateAnimation();

	virtual void	MoveRight(float Value);

	virtual void	UpdateCharacter();
	
	virtual bool	GetIsAttacked();

	virtual void	SetIsAttacked(bool isAttacked);
	
	virtual void	TakeDamages(int damage);


	virtual void	Dead();







protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachinePlayer")
		bool _isAttacked;
	
};
