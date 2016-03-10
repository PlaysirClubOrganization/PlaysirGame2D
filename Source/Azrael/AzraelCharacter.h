// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
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

	TArray<UPaperFlipbook*> * m_animationArray;

	FTimerHandle CountdownTimerHandle;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Caracteristics")
	int _life ;

public:

	virtual void Init();

	UFUNCTION(BlueprintNativeEvent)
	void	Attack();

	virtual void Idle() PURE_VIRTUAL(AAzraelCharacter::Idle, ;);

	virtual void Appear() PURE_VIRTUAL(AAzraelCharacter::Appear, ;);

	virtual void Dead() PURE_VIRTUAL(AAzraelCharacter::Dead, ;);

	/** Called to choose the correct animation to play based on the character's movement state */
	virtual void UpdateAnimation() PURE_VIRTUAL(AAzraelCharacter::UpdateAnimation, ;);;

	virtual void Tick(float DeltaSeconds);

	virtual void UpdateCharacter() PURE_VIRTUAL(AAzraelCharacter::UpdateCharacter, ;);

	/** Called for side to side input */
	void MoveRight(float Value) PURE_VIRTUAL(AAzraelCharacter::MoveRight, ;);

	UFUNCTION(BlueprintPure, Category = SpriteInfo)
	float GetCurrentSpriteLength();


	virtual TArray<UPaperFlipbook* > * GetAnimationPaper();

	virtual UPaperFlipbook * GetFlipbook(AnimationState idAnim);

	virtual void SetCurrentAnim(UPaperFlipbook * Flipbook);


	UPaperFlipbook * GetCurrentSprite();

	
	virtual int GetLife();




	std::string GetType();



	Identity_AI GetIdentity();

	static wchar_t * StrCncatCharW(wchar_t * dst, std::string src);
	static wchar_t * StrCncatCharW(wchar_t * dst, std::string src, int n);

};

static std::string GetAnimationName(int anim)
{
	switch (anim)
	{
	case 0:
		return "appear.appear";
	case 1:
		return "idle.idle";
	case 2:
		return "walk.walk";
	case 3:
		return "attack.attack";
	case 4:
		return "jump.jump";
	case 5:
		return "die.die";
	default:
		return "idle.idle";
	}

}