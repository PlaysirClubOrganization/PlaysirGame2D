// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "UObjectGlobals.h"

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

	/*Save all parameters*/
	UFUNCTION(BlueprintCallable, Category = Saver)
	virtual void SaveData(UAzraelSaver * saver);

	/*load all parameters*/
	UFUNCTION(BlueprintCallable, Category = Saver)
	virtual void LoadData(UAzraelSaver * saver);

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/*Handle Run*/
	//void Running();

	//void StopRunning();

	void PlayerAttack();

	virtual void PlayerJump();

	/*Prepare the right Dash*/
	void Dash();

	bool CanDash();

	UFUNCTION(BlueprintCallable, Category = Action)
	void ResetDash();

	void MoveRight(float value);

	void ResetDoubleJumping();

	void ResetAttack();

	virtual	void TriggerTimeAttack();

	virtual void StopSpiritAttack();

	void SpiritRangeParticle();

	void WallJump();

	void EnablingCrouch();

	void DisablingCrouch();

	void EnablingPilon();

	void DisablingPilon();

	void SpiritX(float value);

	void SpiritY(float value);

	void ResetAnchorTarget();

	void Anchor();

 	UFUNCTION(BlueprintCallable, Category = Action)
	void CrouchAction(bool crouching);

	virtual void Tick(float DeltaSeconds);


protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Caracteristics)
	int _level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	uint32 _canClimb:1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	uint32 _canPilon:1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	uint32 _isClimbing:1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	float _wallJumpPerf;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	ASpiritCharacter * _spiritCharacter;

	USceneComponent *  _targetArrow;

	UPaperFlipbookComponent * _arrow;
	
	int _doubleJumpingTrigger;

	int _dashTrigger;
	
	float _angleSpiritCosinus;
	float _angleSpiritSinus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	float _angleSpirit;

	UParticleSystemComponent * _emitterTemplate;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	AActor * _anchorSelected;
};
