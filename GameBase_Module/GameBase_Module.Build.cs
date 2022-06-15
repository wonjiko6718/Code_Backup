// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameBase_Module : ModuleRules
{
	public GameBase_Module(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" ,"UMG" , "CableComponent", "LevelSequence"});
		PrivateDependencyModuleNames.AddRange(new string[] { "CableComponent" , "LevelSequence" });
		PrivateIncludePathModuleNames.AddRange(new string[] { "CableComponent" , "LevelSequence"});
		PublicIncludePaths.AddRange(new string[] {
			"GameBase_Module/AnimInstance" ,
			"GameBase_Module/Character" ,
			"GameBase_Module/GameMode" ,
			"GameBase_Module/PlayerController" ,
			"GameBase_Module/Scene_Actors"
		});
	}
}
