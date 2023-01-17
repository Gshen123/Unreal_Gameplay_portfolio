// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gameplay_Portfolio : ModuleRules {
	public Gameplay_Portfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(new string[] {});
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "MediaAssets", "UMG","SlateCore", "GameplayTags"});
		
		PublicIncludePaths.AddRange(new string[] { "Gameplay_Portfolio/Widget", "Gameplay_Portfolio/System", "Gameplay_Portfolio/Settings", "Gameplay_Portfolio/Player", "Gameplay_Portfolio/Character"});
	}
}
