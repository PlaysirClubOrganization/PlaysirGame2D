// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AzraelSaver.h"
#include "AzraelSaver.h"
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
	

	virtual void Init();

	virtual bool	GetIsAttacked();

	virtual void	SetIsAttacked(bool isAttacked);
	
	UFUNCTION(BlueprintCallable, Category = Action)
	virtual void AddCoin();

	UFUNCTION(BlueprintCallable, Category = Saver)
	virtual void SaveData(UAzraelSaver * saver);

	UFUNCTION(BlueprintCallable, Category = Saver)
	virtual void LoadData(UAzraelSaver * saver);



protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Caracteristics)
	int _coin;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Caracteristics)
	int _level;


};
