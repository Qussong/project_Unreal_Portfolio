// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GamePortFolio : ModuleRules
{
	public GamePortFolio(ReadOnlyTargetRules Target) : base(Target)
	{
        PublicIncludePaths.AddRange(new string[] { "GamePortFolio" });

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
