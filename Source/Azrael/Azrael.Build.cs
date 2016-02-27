// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Azrael : ModuleRules
{
	public Azrael(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(
                            new string[] { "Core",
                                           "CoreUObject",
                                           "Engine",
                                           "InputCore",
                                           "Paper2D",
                                           "AIModule"
                            });
	}
}
