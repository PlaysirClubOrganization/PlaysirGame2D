// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "UObjectGlobals.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputCoreTypes.h"
#include "Item/Anchor.h"
#include "Grapple.h"
#include "../UMG/Public/Components/WidgetComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "AzraelCharacter.h"
#include "AbstractPlayer.generated.h"




/**
 * 
 */
class UAzraelSaver;


USTRUCT(BlueprintType)
struct FWeapon {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponParameter")
	EWeaponNature weaponNature;

	//damage of the attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponParameter")
	int32 damage;

	//cooldown of the attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponParameter")
	float cooldown;

	void init(int32 Fdamage, float Fcooldown)
	{
		damage = Fdamage;
		cooldown = Fcooldown;
	}

	FWeaponParameter()
	{
		switch (weaponNature)
		{
		case EWeaponNature::Spear: 
			init(20, 0.3);
			break;
		case EWeaponNature::Sword :
			init(50, 0.5);
			break;
		case EWeaponNature::Hammer :
			init(100, 1.5);
			break;
		case EWeaponNature::Scythe :
			init(80, 1.0);
			
		}
	}
};

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

	virtual	void SpiritSight();

	virtual void StopSpiritSight();

	void SpiritRangeParticle();

	void WallJump();

	void EnablingCrouch();

	void DisablingCrouch();

	void EnablingPilon();

	void DisablingPilon();

	void ResetPilon();

	void SpiritX(float value);

	void SpiritY(float value);

	void ExecAction();

	void ResetAction();

	void ResetAnchor();

	UFUNCTION(BlueprintNativeEvent, Category = SpiritAction)
	void GrappleLanch();
	
	UFUNCTION(BlueprintNativeEvent, Category = SpiritAction)
	void AnchorAction();
	
	UFUNCTION(BlueprintNativeEvent, Category = SpiritAction)
	void ExplodeAction();
	
	UFUNCTION(BlueprintNativeEvent, Category = SpiritAction)
	void FreezeAction();
	
	UFUNCTION(BlueprintNativeEvent, Category = SpiritAction)
	void TranspositionAction();

	UFUNCTION(BlueprintPure, Category = Energy)
	int GetSpiritEnergy(ESpiritNature spiritNature);

	UFUNCTION(BlueprintPure, Category = Energy)
	int GetSpiritEnergyMax(ESpiritNature spiritNature);

 	UFUNCTION(BlueprintCallable, Category = Action)
	void CrouchAction(bool crouching);

	void EnablingSights();

	void DisablingSights();

	virtual void Tick(float DeltaSeconds);


protected:
	
	void MakeCircleTrigo();


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Game)
	FWeapon _weapon;

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
	AGrapple * _grapple;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	UWidgetComponent * _sightWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	uint32 _isSightsEnable : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spirit)
	int _dashTrigger;

	int _doubleJumpingTrigger;

	int _triggerPilon;
	
	float _angleSpiritCosinus;

	float _angleSpiritSinus;


};
