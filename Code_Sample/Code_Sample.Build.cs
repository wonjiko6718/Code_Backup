// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Code_Sample : ModuleRules
{
	public Code_Sample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" ,"UMG" , "CableComponent", "LevelSequence" , "GameBase_Module", "Niagara"});
		PrivateDependencyModuleNames.AddRange(new string[] { "CableComponent" , "LevelSequence" , "GameBase_Module"});
		PrivateIncludePathModuleNames.AddRange(new string[] { "CableComponent" , "LevelSequence"});
		PublicIncludePaths.AddRange(new string[] {
			"Code_Sample/Level_Tower" ,
			"Code_Sample/Level_Tower/AnimInstance" ,
			"Code_Sample/Level_Tower/Character" ,
			"Code_Sample/Level_Tower/GameMode" ,
			"Code_Sample/Level_Tower/PlayerController" ,
			"Code_Sample/Level_Tower/Scene_Actors"
		});
	}
}
