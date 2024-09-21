// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GamePortFolio : ModuleRules
{
	public GamePortFolio(ReadOnlyTargetRules Target) : base(Target)
	{
        PublicDefinitions.Add("ENABLE_DRAW_DEBUG=0");

        PublicIncludePaths.AddRange(new string[] { "GamePortFolio" });

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
            "AIModule",
            "NavigationSystem",
            "Niagara",
            "UMG",
			"GameplayTasks",

        });
	}
}
