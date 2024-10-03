// Copyright (c) 2024 Anoho All rights reserved.

using UnrealBuildTool;

public class GameModifiers : ModuleRules
{
	public GameModifiers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[] 
			{ 
				"Core", 
				"CoreUObject", 
				"Engine", 
				"EnhancedInput",
				"GameplayAbilities",
				"GameplayTags",
				"GameplayTasks",
				"InputCore",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
			});
	}
}
