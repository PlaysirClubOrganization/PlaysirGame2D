// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
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
	
	/*Tempory add coin*/
	UFUNCTION(BlueprintCallable, Category = Action)
	virtual void AddCoin();

	/*Save all parameters*/
	UFUNCTION(BlueprintCallable, Category = Saver)
	virtual void SaveData(UAzraelSaver * saver);

	/*load all parameters*/
	UFUNCTION(BlueprintCallable, Category = Saver)
	virtual void LoadData(UAzraelSaver * saver);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/*Handle Run*/
	void Running();

	void StopRunning();

	void PlayerAttack();

	virtual void PlayerJump();

	/*Prepare the right Dash*/
	void Dash();

	void ResetDash();

	void MoveRight(float value);

	void ResetDoubleJumping();

	void ResetAttack();

	virtual	void TriggerTimeAttack();

	virtual void StopAttack();

	void WallJump();

	void EnablingCrouch();

	void DisablingCrouch();

	void EnablingPilon();

	void DisablingPilon();

	UFUNCTION(BlueprintCallable, Category = Action)
	void CrouchAction(bool crouching);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Caracteristics)
	int _coin;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Caracteristics)
	int _level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	bool _canClimb;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	bool _canCrouch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	bool _canPilon;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	bool _isClimbing;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	bool _canRun;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	float _endurance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	float _wallJumpPerf;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	ASpiritCharacter * _spiritCharacter;
	
	int _doubleJumpingTrigger;

	int _dashTrigger;
	
	bool _canDash;

	

	

};
