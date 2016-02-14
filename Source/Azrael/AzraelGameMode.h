// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/GameMode.h"
#include "AzraelGameMode.generated.h"

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.
//
// This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of AzraelCharacter

UCLASS(minimalapi)
class AAzraelGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AAzraelGameMode();
};
