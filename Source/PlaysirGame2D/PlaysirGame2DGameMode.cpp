// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "PlaysirGame2D.h"
#include "PlaysirGame2DGameMode.h"
#include "PlaysirGame2DCharacter.h"

APlaysirGame2DGameMode::APlaysirGame2DGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = APlaysirGame2DCharacter::StaticClass();	
}
