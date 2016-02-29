// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Perception/PawnSensingComponent.h"
#include "AzraelCharacter.h"
#include "Enemy.generated.h"

/**
*
*/
UCLASS(abstract)
class AZRAEL_API AEnemy : public AAzraelCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isAppearing;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isPatrolling;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isWalking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isAttacking;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _IsIdle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _playerDetected;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		UPawnSensingComponent * _pawnSensing;



public:
	UFUNCTION(BlueprintCallable, Category = Initialisation)
		virtual void initEnemy();

	/** Called to choose the correct animation to play based on the character's movement state */
	UFUNCTION()
		virtual void UpdateAnimation();

	/** Called for side to side input */
	UFUNCTION()
		virtual void MoveRight(float Value);

	UFUNCTION()
		virtual void UpdateCharacter();

	virtual void Tick(float DeltaSeconds);

};
