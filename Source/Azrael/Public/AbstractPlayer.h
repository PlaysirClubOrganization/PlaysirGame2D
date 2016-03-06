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
	
	void	UpdateAnimation();

	void	MoveRight(float Value);

	void	UpdateCharacter();

private:



	
	
	
};
