// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Perception/PawnSensingComponent.h"
#include "PaperFlipbookComponent.h"
#include "Azrael.h"
#include "AzraelCharacter.h"
#include "Enemy.generated.h"

/*The Type of the Character :
- Zombie
- Vampire
- Golem ,etc..
*/
UENUM(BlueprintType)
enum class Identity_AI : uint8 {
	Zombie UMETA(DisplayName = "Zombie"),
	Vampire UMETA(DisplayName = "Vampire")
};




/**
*
*/
UCLASS()
class AZRAEL_API AEnemy : public AAzraelCharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Identity)
		Identity_AI _identity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		int _nbKilled ;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isAppearing;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "  AI")
		bool _isPatrolling;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _isDead;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool _playerDetected;

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

	std::string GetType();

	virtual Identity_AI GetIdentity();

	wchar_t * StrCncatCharW(wchar_t * dst, std::string src);
	wchar_t * StrCncatCharW(wchar_t * dst, std::string src,int n);



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

