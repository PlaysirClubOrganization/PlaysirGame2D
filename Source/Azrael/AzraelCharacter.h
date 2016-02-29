// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "PaperCharacter.h"
#include "AzraelCharacter.generated.h"

// This class is the default character for Azrael, and it is responsible for all
// physical interaction between the player and the world.
//
//   The capsule component (inherited from ACharacter) handles collision with the world
//   The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
//   The Sprite component (inherited from APaperCharacter) handles the visuals



UCLASS(abstract)
class AAzraelCharacter : public APaperCharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
		UPaperFlipbook*  _currentAnim;

	TMap<uint8, UPaperFlipbook*> m_animationMap;

	enum AnimationState : uint8 {
		Appear_Animation,
		Idle_Animation,
		Run_Animation,
		Attack_Animation,
		Jump_Animation,
		Die_Animation
	};


	/*The Type of the Character :
	- Zombie
	- Vampire
	- Golem ,etc..
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Identity)
		FString _identity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Caracteristics")
		int _life;


public:

	virtual void init();

	UFUNCTION(BlueprintCallable, Category = StateMachine)
		virtual void Attack() PURE_VIRTUAL(AAzraelCharacter::Attack, ;);

	UFUNCTION(BlueprintCallable, Category = StateMachine)
		virtual void Appear() PURE_VIRTUAL(AAzraelCharacter::Appear, ;);

	UFUNCTION(BlueprintCallable, Category = StateMachine)
		virtual void Dead() PURE_VIRTUAL(AAzraelCharacter::Dead, ;);

	/** Called to choose the correct animation to play based on the character's movement state */
	UFUNCTION(BlueprintCallable, Category = StateMachine)
		virtual void UpdateAnimation() PURE_VIRTUAL(AAzraelCharacter::UpdateAnimation, ;);;

	virtual void Tick(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = StateMachine)
		virtual void UpdateCharacter() PURE_VIRTUAL(AAzraelCharacter::UpdateCharacter, ;);

	/** Called for side to side input */
	void MoveRight(float Value) PURE_VIRTUAL(AAzraelCharacter::MoveRight, ;);


	virtual TMap<uint8, UPaperFlipbook* > getAnimationPaper();

	virtual UPaperFlipbook * getFlipbook(uint8 idAnim);

};
