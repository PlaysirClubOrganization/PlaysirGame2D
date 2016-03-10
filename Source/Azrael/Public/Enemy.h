// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Perception/PawnSensingComponent.h"
#include "PaperFlipbookComponent.h"
#include "Azrael.h"
#include "AbstractPlayer.h"

#include "AzraelCharacter.h"
#include "Enemy.generated.h"

#define TIME_FOR_ATTACK .1f





/**
*
*/
UCLASS()
class AZRAEL_API AEnemy : public AAzraelCharacter
{
	GENERATED_BODY()

protected:



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		int _nbKilled ;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isAppearing;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "  AI")
		bool _isPatrolling;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isWalking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isAttacking;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _playerDetected;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _lookAtRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		UPawnSensingComponent * _pawnSensing;

public:
	
	AEnemy();

	~AEnemy();

	UFUNCTION(BlueprintCallable, Category = Initialisation)
	virtual void Appear();

	/** Called to choose the correct animation to play based on the character's movement state */
	UFUNCTION()
	virtual void UpdateAnimation();

	/** Called for side to side input */
	UFUNCTION()
	virtual void MoveRight(float Value);

	UFUNCTION()
	virtual void UpdateCharacter();

	virtual void Tick(float DeltaSeconds);

	UFUNCTION()
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = StateMachine)
	virtual void Dead();
	
	UFUNCTION(BlueprintCallable, Category = StateMachine)
	virtual void Init();
	
	UFUNCTION(BlueprintCallable, Category = StateMachine)
	virtual void Idle();

	UFUNCTION(BlueprintCallable, Category = StateMachine)
	virtual void Patrol();
	
	UFUNCTION(BlueprintNativeEvent)
	void Attack();


	void SetPlayerAttacked(bool attack);

	void initAttack();

	int GetDirection();





};


