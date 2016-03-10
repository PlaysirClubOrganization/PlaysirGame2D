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


/*The Type of the Character :
- Zombie
- Vampire
- Golem ,etc..
*/
UENUM(BlueprintType)
enum class Identity_AI : uint8 {
	Zombie UMETA(DisplayName = "Zombie"),
	Vampire UMETA(DisplayName = "Vampire"),
	Golem UMETA(DisplayName = "Golem"),
	Skeleton UMETA(DisplayName = "Skeleton"),
	MAX_ENUM_IDENTITY
};


UCLASS(abstract)
class AAzraelCharacter : public APaperCharacter
{
	GENERATED_BODY()
protected:
	//The current PaperFlipbook of the Pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	UPaperFlipbook*  _currentAnim;

	// An array Of the PaperFlipbook of the pawn
	TArray<UPaperFlipbook*> * m_animationArray;

	FTimerHandle CountdownTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Identity)
	Identity_AI _identity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Caracteristics")
	int _life ;
	//Is the life of the pawn is less  than 0
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Caracteristics")
	bool _isDead;
	
	//Is the Pawn is appearing
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Caracteristics")
	bool _isAppearing;

	//Is the enemy triggers an attack
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	bool _isAttacked;
	
	// Is the Pawn walking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	bool _isWalking;

	//Is the Pawn Jumping
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	bool _isJumping;

	//Is the Pawn Attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StateMachine")
	bool _isAttacking;

public:

	//@unusedNow Called in the constructor 
	virtual void Init();

	/** When the Pawn Attack we set the Attack_Animation PaperFlipbook
	*
	*/
	UFUNCTION(BlueprintNativeEvent)
	void	Attack();

	/** When the Pawn Idle we set the Idle_Animation PaperFlipbook
	*
	*/
	virtual void Idle() PURE_VIRTUAL(AAzraelCharacter::Idle, ;);

	/** When the Pawn Appear we set the Appear_Animation PaperFlipbook
	*	and set the _isAppearParameter to true
	*/
	virtual void Appear() PURE_VIRTUAL(AAzraelCharacter::Appear, ;);

	/**
	* When the life of the Pawn is less (or equal) than 0
	* we put the Dead_animationa and destroy the Pawn
	*/	
	virtual void Dead() PURE_VIRTUAL(AAzraelCharacter::Dead, ;);

	/** Called to choose the correct animation to play based on the character's movement state */
	virtual void UpdateAnimation() PURE_VIRTUAL(AAzraelCharacter::UpdateAnimation, ;);;

	virtual void Tick(float DeltaSeconds);

	virtual void UpdateCharacter() PURE_VIRTUAL(AAzraelCharacter::UpdateCharacter, ;);

	/** Called for side to side input */
	void MoveRight(float Value) PURE_VIRTUAL(AAzraelCharacter::MoveRight, ;);

	/**
	*
	* @return The time Lenght of the current Animation PaperFlipbook
	*/
	UFUNCTION(BlueprintPure, Category = SpriteInfo)
	float GetCurrentSpriteLength();

	/**
	*@return the pointer of the Array containing of the PaperFlipbook of the pawn
	*/
	virtual TArray<UPaperFlipbook* > * GetAnimationPaper();

	/**
	*@param [AnimationState] idAnim : The State Animation Desired  
	*@return the pointer of the Flipbook of the idAnim AnimationState 
	*	{Appear_Animation ; Idle_Animation ; Attack_Animation, ect..}
	*/
	virtual UPaperFlipbook * GetFlipbook(AnimationState idAnim);

	/**
	* @param [UPaperFlipbook *] flipbook : the new animation flipbook
	* Update the animation to flipbook
	*/
	virtual void SetCurrentAnim(UPaperFlipbook * Flipbook);

	/**
	* @return : The Current Animation PaperFlipbook
	*/
	UPaperFlipbook * GetCurrentSprite();

	/**
	* @return the life of the Pawn
	*/
	virtual int GetLife();

	/**
	*@return the of the path of the flipbook directory
	*
	*	exemple for Zombie => '\Zombie\Flipbook\' 
	*/
	std::string GetType();

	/**
	*@return the Identity of the pawn as an Enum instance of Identity
	* {Zombie,Vampire,Golem,Skeleton,... }
	*/
	Identity_AI GetIdentity();

	/**
	*Used to concat wchar_t with string
	*/
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





/*
* FConstructorStatics will automatically load the different sprite of the any character by giving
* the right id in the init function.
*
* @warning : The project must bu construct
*/
static struct FConstructorStatics
{
	//An Array which stores the 2D Animation Instance (UPaperFlipbook)
	TArray<ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>> AnimationInstance;

	//Constructor
	FConstructorStatics(AAzraelCharacter *perso)
		: AnimationInstance(TArray<ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>>())
	{
		//The beginning of the path of the sprite
		wchar_t * tmp = L"/Game/Azrael/Enemy/\0";

		//Getting the type of the AI (Zombie, Vampire, ...)
		std::string t = perso->GetType();

		//Concat the beginning of the path of the sprite and the AI'type 
		// exemple => "/Game/Azrael/Enemy/ + Zombie/Flipbook/
		wchar_t *dst = perso->StrCncatCharW(tmp, perso->GetType(), 19);

		//For loop in order to Get all sprites Animation which are in the folder
		for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; i++)
		{
			//Adding the PaperFlipbook in the TArray
			//GetAnimationName return a string : appear.apper, idle.idle, etc...
			AnimationInstance.Add(ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>
				(perso->StrCncatCharW(dst, GetAnimationName(i))));
		}
	}

	~FConstructorStatics()
	{
	}

};