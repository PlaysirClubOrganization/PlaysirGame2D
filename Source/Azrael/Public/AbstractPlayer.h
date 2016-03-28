// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AzraelCharacter.h"
#include "AbstractPlayer.generated.h"

/**
 * 
 */
class UAzraelSaver;

UCLASS(abstract)
class AZRAEL_API AAbstractPlayer : public AAzraelCharacter
{
	GENERATED_BODY()

public:
	friend class ASpiritCharacter;

	virtual void Init();
	
	UFUNCTION(BlueprintCallable, Category = Action)
	virtual void AddCoin();

	UFUNCTION(BlueprintCallable, Category = Saver)
	virtual void SaveData(UAzraelSaver * saver);

	UFUNCTION(BlueprintCallable, Category = Saver)
	virtual void LoadData(UAzraelSaver * saver);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void TriggerTimeAttack();

	void StopAttack();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Caracteristics)
	int _coin;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Caracteristics)
	int _level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	ASpiritCharacter * _spiritCharacter;

};
