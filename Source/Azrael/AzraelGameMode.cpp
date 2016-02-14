// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Azrael.h"
#include "AzraelGameMode.h"
#include "AzraelCharacter.h"

AAzraelGameMode::AAzraelGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = AAzraelCharacter::StaticClass();	
}
