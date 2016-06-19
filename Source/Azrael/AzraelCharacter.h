// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "PaperCharacter.h"
#include "Azrael.h"
#include "AzraelCharacter.generated.h"



// This class is the default character for Azrael, and it is responsible for all
// physical interaction between the player and the world.
//

/****************************************************************************/
/* This class is the base class of All the Pawn, The controlled Pawn or AI  */
/* @info : this class is abstract											*/
/****************************************************************************/
class UPaperFlipbook;


UCLASS(abstract)
class AAzraelCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = Info)
	virtual int GetPawnDirection();

	UFUNCTION(BlueprintCallable, Category = Info)
	virtual void TurnPawnRotation();

	//@used in the ChildClass Called in the constructor
	UFUNCTION(BlueprintCallable, Category = StateMachine)
	virtual void Init();

	UFUNCTION(BlueprintCallable, Category = Damage)
	void TakeDamages(int damage);

	/** Called to choose the correct animation to play based on the character's movement state */
	virtual void UpdateAnimation();

	/*Event UE4 API : this is executed when the level begins*/
	virtual void BeginPlay();


	virtual void Tick(float DeltaSeconds);

	virtual void UpdateCharacter();


	/**
	*
	* @return The time Lenght of the current Animation PaperFlipbook
	*/
	UFUNCTION(BlueprintPure, Category = SpriteInfo)
	float GetCurrentSpriteLength();

	/**
	*@return the pointer of the Array containing of the PaperFlipbook of the pawn
	*/
	virtual TArray<class UPaperFlipbook* > * GetAnimationPaper();

	/**
	*@param [AnimationState] idAnim : The State Animation Desired  
	*@return the pointer of the Flipbook of the idAnim AnimationState 
	*	{Appear_Animation ; Idle_Animation ; Attack_Animation, ect..}
	*/
	virtual class UPaperFlipbook * GetFlipbook(AnimationState idAnim);

	/**
	* @param [UPaperFlipbook *] flipbook : the new animation flipbook
	* Update the current  animation to flipbook
	*/
	virtual void SetCurrentAnim(class UPaperFlipbook * Flipbook);

	/**
	* @return : The Current Animation PaperFlipbook
	*/
	class UPaperFlipbook * GetCurrentSprite();

	/**
	* @return the life of the Pawn
	*/
	virtual int GetLife() const;


	virtual void SetLife(int life);


	/** When the Pawn Attack we set the Attack_Animation PaperFlipbook
	*
	*/
	UFUNCTION(BlueprintCallable, Category = Attacking)
		virtual void Attacking();

	/** When the Pawn Idle we set the Idle_Animation PaperFlipbook
	*
	*/
	UFUNCTION(BlueprintCallable, Category = StateMachine)
		virtual void Idle();

	/** When the Pawn Appear we set the Appear_Animation PaperFlipbook
	*	and set the _isAppearParameter to true
	*/
	UFUNCTION(BlueprintCallable, Category = StateMachine)
		virtual void Appear();

	/**
	* When the life of the Pawn is less (or equal) than 0
	* we put the Dead_animationa and destroy the Pawn
	*/
	virtual void Dead();

	/**
	* @return if the Pawn is Dying
	*/
	virtual bool IsDead() const;

	/**
	* @return if the Pawn is Appearing
	*/
	virtual bool IsAppearing() const;

	/**
	* @return if the Pawn is Walking
	*/
	virtual bool IsWalking() const;
	
	/**
	* @return if the Pawn is Attacked
	*/
	virtual bool IsAttacked() const;

	/**
	* @return if the Pawn is Attacking
	*/
	virtual bool IsAttacking() const;

	/**
	* @return if the Pawn is Jumping
	*/
	virtual bool IsPawnJumping() const;

	/**
	* @return if the Pawn is Crouching
	*/
	virtual bool IsCrouching() const;

	/**
	* @return if the Pawn is Sliding
	*/
	virtual bool IsSliding() const;

	/**
	* @param : isJumping
	* enable or disable the jump stateMachine
	*/
	virtual void SetJumping(bool isJumping);
	
	/**
	* @param : isAttacking
	* enable or disable the attack stateMachine
	*/
	virtual void SetAttacking(bool isAttacking);
	
	/**
	* @param : isAttacked
	* enable or disable the attacked stateMachine
	*/
	virtual void SetAttacked(bool isAttacked);
	
	/**
	* @param : isWalking
	* enable or disable the walk stateMachine
	*/
	virtual void SetWalking(bool isWalking);
	
	/**
	* @param : isAppearing
	* enable or disable the appear stateMachine
	*/
	virtual void SetAppearing(bool isAppearing);

	/**
	* @param : isCrounching
	* enable or disable the crouch stateMachine
	*/
	virtual void SetCrouching(bool isCrouching);

	/**
	* @param : isSliding
	* enable or disable the crouch stateMachine
	*/
	virtual void SetSliding(bool isSliding);
	
	/**
	* @param : isDead
	* enable or disable the dead stateMachine
	*/
	virtual void  SetDead(bool isDead);

	virtual bool  GetIsAttacked();

	virtual void  SetIsAttacked(bool isAttacked);

	virtual bool  IsRunning();

	virtual void SetRunning(bool isRunning);

	virtual void Running();

	virtual void StopRunning();

	virtual float GetPawnAttackDamages();

	virtual float GetRangeAttack();

	virtual float GetForceAttack();

	/**
	*@return the Identity of the pawn as an Enum instance of Identity
	* {Zombie,Vampire,Golem,Skeleton,... }
	*/
	Identity GetIdentity();


	/**
	*@return the of the path of the Flipbook directory
	*
	*	example for Zombie => '\Zombie\Flipbook\'
	*/
	std::string GetType();
	FString GetTypeAsFString();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attacking)
	AAzraelCharacter * _receiverAttack;

	// An array Of the PaperFlipbook of the pawn
	TArray<class UPaperFlipbook*>  * _animationArray;

	//The timer which be used to delegate method in order to play some
	// flipbook (for example playing the death anim before destroying it)
	FTimerHandle _countdownTimerHandle;

	//This Identity of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Identity)
	Identity _identity;

	//The life of the Pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Caracteristics")
	int _life;

	//Is the life of the pawn is less  than 0
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Caracteristics")
	uint32 _isDead:1;

	//Is the Pawn is appearing
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Caracteristics")
	uint32 _isAppearing:1;

	//Is the enemy triggers an attack
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	uint32 _isAttacked:1;

	// Is the Pawn walking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	uint32 _isWalking:1;

	//Is the Pawn Jumping
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	uint32 _isJumping:1;

	//Is the Pawn Attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	uint32 _isAttacking:1;

	//Is the character crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	uint32 _isCrouching:1;

	//Is the character crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	uint32 _isSliding:1;

	//Is the Pawn Running
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	uint32 _isRunning:1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	uint32 _canCrouch : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	uint32 _canRun : 1;

	/*
	* Is the Pawn's looking at right or left
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Direction")
	uint32 _lookAtRight:1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Action)
	float _endurance;

	/*
	* The Force impact that will affect the enemy
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float _forceAttack;
};


