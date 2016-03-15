// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Perception/PawnSensingComponent.h"
#include "PaperFlipbookComponent.h"
#include "Azrael.h"
#include "AbstractPlayer.h"

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

	/*Used for the Zombie_AI and Skeleton_AI
	*
	*	If the AI is killed we respawn the Ai with 
	*	a reduced life proportional to the nbKilled  
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		int _nbKilled ;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "  AI")
		bool _isPatrolling;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _playerDetected;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _lookAtRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isImmobile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		UPawnSensingComponent * _pawnSensing;


public:
	
	UFUNCTION(BlueprintCallable, Category = Constructor)
	virtual void Init();


	UFUNCTION()
	virtual void UpdateCharacter();



	UFUNCTION(BlueprintCallable, Category = StateMachine)
	virtual void Dead();

	UFUNCTION(BlueprintCallable, Category = StateMachine)
	virtual void Patrol();
	
	UFUNCTION(BlueprintNativeEvent)
	void Attack();

	virtual void SetPlayerAttacked(bool attack);

	virtual int GetDirection();





};

