// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "UObjectGlobals.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputCoreTypes.h"
#include "Item/Anchor.h"
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

	void ResetPilon();

	void SpiritX(float value);

	void SpiritY(float value);

	void ResetAnchorTarget();

	void Anchor();

	UFUNCTION(BlueprintCallable, Category = Energy)
	int GetSpiritEnergy(SpiritNature spiritNature);

	UFUNCTION(BlueprintCallable, Category = Energy)
	int GetSpiritEnergyMax(SpiritNature spiritNature);

 	UFUNCTION(BlueprintCallable, Category = Action)
	void CrouchAction(bool crouching);

	virtual void Tick(float DeltaSeconds);


protected:
	
	void MakeCircleTrigo();




	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Game)
	int _level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	uint32 _canClimb:1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	uint32 _isPiloning :1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	uint32 _isClimbing:1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	float _wallJumpPerf;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	float _dashDelay;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	ASpiritCharacter * _spiritCharacter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	float _angleSpirit;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	AAnchor * _anchorSelected;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	int _dashTrigger;



	UParticleSystemComponent * _emitterTemplate;

	int _doubleJumpingTrigger;

	int _triggerPilon;

	uint32 _anchorMovement : 1;

	
	float _angleSpiritCosinus;

	float _angleSpiritSinus;


};
