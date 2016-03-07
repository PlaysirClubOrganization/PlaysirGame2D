// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

// This file is the private precompiled header for your game.
// You must include it first in each .cpp file.
//
// Place any includes here that are needed by the majority of your .cpp files
#include <iostream>
#include "EngineMinimal.h"

TArray<FString> GetAllFilesInDirectory(const FString directory, const bool fullPath,
	const FString onlyFilesStartingWith, const FString onlyFilesWithExtension);



static enum AnimationState : uint8 {
	Appear_Animation,
	Idle_Animation,
	Walk_Animation,
	Attack_Animation,
	Jump_Animation,
	Dead_Animation,
	MAX_ENUM
};

