// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AzraelCharacter.h"
#include "SpiritCharacter.generated.h"


USTRUCT(BlueprintType)
struct FSpiritParameter{

	GENERATED_BODY()
	
	//the range of the attack of the spirit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpiritNatureParameter")
	int32 rangeAttack;

	//the range of the special action of the spirit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpiritNatureParameter")
	int32 rangeAction;
	
	//the energy of the spirit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpiritNatureParameter")
	int32 energyMax;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpiritNatureParameter")
	int32 currentEnergy;

	//the time between two action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpiritNatureParameter")
	float delayBetweenAction;

	//the max time the spirit can be slowed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpiritNatureParameter")
	float timeSlowed;


	FSpiritParameter(int32 FrangeAttack,int32 FrangeAction, int32 FenergyMax, float FdelayBetweenAction, float FtimeSlowed)
	{
		rangeAttack = FrangeAttack;
		rangeAction = FrangeAction;
		energyMax = currentEnergy = FenergyMax;
		delayBetweenAction = FdelayBetweenAction;
		timeSlowed = FtimeSlowed;
	}

	FSpiritParameter()
	{
		rangeAttack = 700;
		rangeAction = 700;
		energyMax = currentEnergy = 100;
		delayBetweenAction = 2.0;
		timeSlowed = 2.0;
	}
};


/**
 * 
 */
UCLASS()
class AZRAEL_API ASpiritCharacter : public AAzraelCharacter
{
	GENERATED_BODY()
public:

	//************************************
	// Method:    ASpiritCharacter
	// FullName:  ASpiritCharacter::ASpiritCharacter
	// Access:    public 
	// Returns:   
	// Qualifier: The constructor of the class
	//************************************
	ASpiritCharacter();

	//************************************
	// Method:    Init
	// FullName:  ASpiritCharacter::Init
	// Access:    virtual public 
	// Returns:   void
	// Qualifier:
	//************************************
	virtual void Init();

	//************************************
	// Method:    IsMasteringTime
	// FullName:  ASpiritCharacter::IsMasteringTime
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	//************************************
	UFUNCTION(BlueprintPure, Category = spirit)
	bool IsTimeDilated();

	//************************************
	// Method:    GetSpecialSpiritRange
	// FullName:  ASpiritCharacter::GetSpecialSpiritRange
	// Access:    public 
	// Returns:   float
	// Qualifier:
	//************************************
	float GetSpecialSpiritRange();

	//************************************
	// Method:    GetRangeAttack
	// FullName:  ASpiritCharacter::GetRangeAttack
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: SpiritNature spiritNature
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	int GetSpiritRangeAttack(ESpiritNature spiritNature);
	
	//************************************
	// Method:    GetCurrentRangeAttack
	// FullName:  ASpiritCharacter::GetCurrentRangeAttack
	// Access:    public 
	// Returns:   int
	// Qualifier:
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	int GetCurrentSpiritRangeAttack();
	
	//************************************
	// Method:    GetRangeAction
	// FullName:  ASpiritCharacter::GetRangeAction
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: SpiritNature  spiritNature
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	int GetRangeAction(ESpiritNature spiritNature);
	
	//************************************
	// Method:    GetCurrentRangeAction
	// FullName:  ASpiritCharacter::GetCurrentRangeAction
	// Access:    public 
	// Returns:   int
	// Qualifier:
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	int GetCurrentRangeAction();

	//************************************
	// Method:    GetEnergy
	// FullName:  ASpiritCharacter::GetEnergy
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: SpiritNature  spiritNature
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	int GetEnergy(ESpiritNature spiritNature);

	//************************************
	// Method:    GetEnergyMax
	// FullName:  ASpiritCharacter::GetEnergyMax
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: SpiritNature  spiritNature
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	int GetEnergyMax(ESpiritNature spiritNature);

	//************************************
	// Method:    GetTimeBetweenAction
	// FullName:  ASpiritCharacter::GetTimeBetweenAction
	// Access:    public 
	// Returns:   float
	// Qualifier:
	// Parameter: SpiritNature  spiritNature
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	float GetTimeBetweenAction(ESpiritNature spiritNature);

	//************************************
	// Method:    GetCurrentTimeBetweenAction
	// FullName:  ASpiritCharacter::GetCurrentTimeBetweenAction
	// Access:    public 
	// Returns:   float
	// Qualifier:
	// Parameter: SpiritNature  spiritNature
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	float GetCurrentTimeBetweenAction();

	//************************************
	// Method:    GetTimeSlowed
	// FullName:  ASpiritCharacter::GetTimeSlowed
	// Access:    public 
	// Returns:   float
	// Qualifier:
	// Parameter: SpiritNature  spiritNature
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	float GetTimeSlowed(ESpiritNature spiritNature);

	//************************************
	// Method:    GetCurrentTimeSlowed
	// FullName:  ASpiritCharacter::GetCurrentTimeSlowed
	// Access:    public 
	// Returns:   float
	// Qualifier:
	// Parameter: SpiritNature  spiritNature
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	float GetCurrentTimeSlowed();


	//************************************
	// Method:    GetCurrentSpiritNature
	// FullName:  ASpiritCharacter::GetCurrentSpiritNature
	// Access:    public 
	// Returns:   SpiritNature
	// Qualifier:
	//************************************
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = SpiritParameter)
	ESpiritNature GetCurrentSpiritNature();
	
	UParticleSystemComponent * GetParticuleActionRange();

	void SetTimeDilated(bool isTimeSlowed);

	void SetParticuleActionRange(UParticleSystemComponent * particule);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spirit)
	float _actionSpiritRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spirit)
	uint32 _canAttack:1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spirit)
	uint32 _isTimeDilated : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spirit)
	ESpiritNature _currentSpiritNature;

	TMap<ESpiritNature, FSpiritParameter> _spiritNatureParameter;

	UParticleSystemComponent * _particuleActionRange;

	UParticleSystemComponent * _particuleAttackRange;




};
