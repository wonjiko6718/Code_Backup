// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Code_Sample : ModuleRules
{
	public Code_Sample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
