// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

// This file is the private precompiled header for your game.
// You must include it first in each .cpp file.
//
// Place any includes here that are needed by the majority of your .cpp files
#include <iostream>
#include "Engine.h"
#include "PaperFlipbook.h"

#define TIMER_DEFAULT 0.12f
#define TIME_FOR_ATTACK .19f
#define GetPlayer() (AAbstractPlayer *)UGameplayStatics::GetPlayerPawn(GetWorld(), 0) 
#define ENEMY_PATH_FOLDER  "/Game/Azrael/Enemy/"
#define RUN_SPEED 750.0f;
#define WALK_SPEED 400.0f;
#define CROUCH_SPEED 100.0f
#define BRAKING_DECELERATION_FALLING 12.0f 
#define BRAKING_DECELERATION_WALKING 2048.0f
#define RADIUS 40.0f
#define HEIGHT 90.0f
#define DASH_DELAY 0.4f


static enum AnimationState : uint8 {
	Appear_Animation,// UMETA(DisplayName = "Appear_Animation"),
	Idle_Animation,//UMETA(DisplayName = "Idle_Animation"),
	Walk_Animation,//UMETA(DisplayName = "Walk_Animation"),
	Attack_Animation,// UMETA(DisplayName = "Attack_Animation"),
	Jump_Animation,//UMETA(DisplayName = "Jump_Animation"),
	Dead_Animation, //UMETA(DisplayName = "Dead_Animation")
	Crouch_Animation, //UMETA(DisplayName = "Dead_Animation")
	MAX_ENUM_ANIMATION_STATE
};



UENUM(BlueprintType)
enum class Item_Collectable : uint8 {
	Coin UMETA(DisplayName = "Coin"),
	Key UMETA(DisplayName = "Key"),
	Potion UMETA(DisplayName = "Potion"),
	MAX_ENUM_ITEM
};

UENUM(BlueprintType)
enum class Item_Trap : uint8 {
	Spike UMETA(DisplayName = "Spike"),
	MAX_ENUM_TRAP
};

/*The Type of the Character :
- Zombie
- Vampire
- Golem ,etc..
*/
UENUM(BlueprintType)
enum class Identity : uint8 {
	Skeleton UMETA(DisplayName = "Skeleton"),
	Zombie UMETA(DisplayName = "Zombie"),
	Vampire UMETA(DisplayName = "Vampire"),
	Ghost UMETA(DisplayName = "Ghost"),
	Golem UMETA(DisplayName = "Golem"),
	Player UMETA(DisplayName = "Player"),
	MAX_ENUM_IDENTITY
};

/** Defines the different SpiritNature */
UENUM(BlueprintType)
enum class SpiritNature: uint8
{
	Red,
	Blue,
	Green,
	Yellow
};


//TEMPLATE Load Obj From Path
template <typename ObjClass>
static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
}
// Load PS From Path 
static FORCEINLINE UPaperFlipbook* LoadFlipbook(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UPaperFlipbook>(Path);
}

static FORCEINLINE UParticleSystem* LoadParticle(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UParticleSystem>(Path);
}

static FORCEINLINE UBlueprint* LoadBlueprint(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UBlueprint>(Path);
}

/*Used for the LoadObjFromPath*/
static FString GetAnimationNameAsFString(int anim)
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
	case 6:
		return "crouch.crouch";
	default:
		return "idle.idle";
	}
}

// /*
// // / *
// // // / *
// // // // / *
// // // // // / *
// // // // // // / *
// // // // // // // / *
// // // // // // // // / *
// // // // // // // // // / *
// // // // // // // // // // / *
// // // // // // // // // // // / *
// // // // // // // // // // // // 
// // // // // // // // // // // // //
// // // // // // // // // // // // ///  UNUSED*
// // // // // // // // // // // * /
// // // // // // // // // // * /
// // // // // // // // // * /
// // // // // // // // * /
// // // // // // // * /
// // // // // // * /
// // // // // * /
// // // // * /
// // // * /
// // * /
// */

/*Used for the FConstructorStatics*/
//
//static std::string GetAnimationName(int anim)
//{
//	switch (anim)
//	{
//	case 0:
//		return "appear.appear";
//	case 1:
//		return "idle.idle";
//	case 2:
//		return "walk.walk";
//	case 3:
//		return "attack.attack";
//	case 4:
//		return "jump.jump";
//	case 5:
//		return "die.die";
//	default:
//		return "idle.idle";
//	}
//}
//* FConstructorStatics will automatically load the different sprite of the any character by giving
//* the right id in the init function.
//*
//* @warning : The project must bu construct
//*/
//static struct FConstructorStatics
//{
//	//An Array which stores the 2D Animation Instance (UPaperFlipbook)
//	TArray<ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>> AnimationInstance;
//
//	//Constructor
//	FConstructorStatics(AAzraelCharacter *perso)
//		: AnimationInstance(TArray<ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>>())
//	{
//
//		//The beginning of the path of the sprite
//		wchar_t * tmp = L"/Game/Azrael/Enemy/\0";
//
//		//Getting the type of the AI (Zombie, Vampire, ...)
//		std::string t = perso->GetType();
//
//		//Concat the beginning of the path of the sprite and the AI'type 
//		// exemple => "/Game/Azrael/Enemy/ + Zombie/Flipbook/
//		wchar_t *dst = perso->StrCncatCharW(tmp, perso->GetType());
//
//		//For loop in order to Get all sprites Animation which are in the folder
//		for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; i++)
//		{
//			auto path = perso->StrCncatCharW(dst, GetAnimationName(i));
//			//Adding the PaperFlipbook in the TArray
//			//GetAnimationName return a string : appear.apper, idle.idle, etc...
//			AnimationInstance.Add(ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>
//				(path));
//		}
//	}
//
//	~FConstructorStatics()
//	{
//	}
//
//};

/************************************************************************/
/*	Function for concat wchar_t and string                              */
/************************************************************************/
//wchar_t * AAzraelCharacter::StrCncatCharW(wchar_t * dst, std::string src)
//{
//	//Getting the lenght of the wchar_t
//	int n = wcslen(dst);
//
//	//Allocate the precise size for the final wchar_t
//	wchar_t * d = (wchar_t *)malloc(sizeof(wchar_t) * (1 + n + src.size()));
//
//	// make the affectation d = dst we cannot concat dst with str directly 
//	// because of the precise memory that we need also we will have some 
//	// Chinese and Arabic and Mesopotamians letter in our result 
//	for (int i = 0; i < n; ++i)
//	{
//		d[i] = dst[i];
//	}
//	//Now we append the src
//	for (int i = 0; i < src.size(); ++i)
//	{
//		d[n + i] = src[i];
//	}
//	//We finish a wchar_t t with the \0 character
//	d[n + src.size()] = L'\0';
//	return d;
//}

