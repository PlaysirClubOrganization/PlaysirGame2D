// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

// This file is the private precompiled header for your game.
// You must include it first in each .cpp file.
//
// Place any includes here that are needed by the majority of your .cpp files
#include <iostream>
#include "EngineMinimal.h"

#define GetPlayer() (AAbstractPlayer *)UGameplayStatics::GetPlayerPawn(GetWorld(), 0) 


static enum AnimationState : uint8 {
	Appear_Animation,// UMETA(DisplayName = "Appear_Animation"),
	Idle_Animation,//UMETA(DisplayName = "Idle_Animation"),
	Walk_Animation,//UMETA(DisplayName = "Walk_Animation"),
	Attack_Animation,// UMETA(DisplayName = "Attack_Animation"),
	Jump_Animation,//UMETA(DisplayName = "Jump_Animation"),
	Dead_Animation, //UMETA(DisplayName = "Dead_Animation")
	MAX_ENUM_ANIMATION_STATE
};



UENUM(BlueprintType)
enum class Item_Collectable : uint8 {
	Coin UMETA(DisplayName = "Coin"),
	Key UMETA(DisplayName = "Key"),
	KeyHold UMETA(DisplayName = "KeyHold"),
	Potion UMETA(DisplayName = "Potion"),
	MAX_ENUM_ITEM
};

UENUM(BlueprintType)
enum class Item_Trap : uint8 {
	Spike UMETA(DisplayName = "Spike"),
	MAX_ENUM_TRAP
};

