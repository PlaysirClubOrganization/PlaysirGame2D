// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Azrael.h"
#include "Enemy.generated.h"

class AAzraelCharacter;
class UPawnSensingComponent;
/**
*
*/
UCLASS(abstract)
class AZRAEL_API AEnemy : public AAzraelCharacter
{
	GENERATED_BODY()

protected:

	/*Used for the Zombie_AI and Skeleton_AI
	*
	*	If the AI is killed we respawn the Ai with 
	*	a reduced life proportional to the nbKilled  
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		int _nbKilled ;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "  AI")
	uint32 _isPatrolling:1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	uint32 _playerDetected:1;

	/*
	*	If the true the Pawn is stopped and doesn't move
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	uint32 _isImmobile:1;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	uint32 _isTrapDetected:1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	UPawnSensingComponent * _pawnSensing;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "AI")
	float _pawnAttackDamages;

public:
	
	/******************************************************************************/
	/* Init function, here we load the Paperflipbooks and the the appear animation*/
	/******************************************************************************/
	UFUNCTION(BlueprintCallable, Category = Constructor)
	virtual void Init();


	UFUNCTION()
	virtual void UpdateCharacter();

	/**************************************************************************************/
	/* Whe the Pawn's life is les than 0 we play the dead animation and restart level   */
	/**************************************************************************************/
	/*UFUNCTION(BlueprintCallable, Category = StateMachine)
	virtual void Dead();*/

	UFUNCTION(BlueprintCallable, Category = StateMachine)
	virtual void Patrol();



	virtual float GetRangeAttack();


	virtual float GetPawnAttackDamages();



};

