// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "AzraelSaver.generated.h"

/**
 * 
 */
UCLASS()
class AZRAEL_API UAzraelSaver : public USaveGame
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Player)
	int life;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	int level;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,  Category = Player)
	int count;

	UAzraelSaver();
};
