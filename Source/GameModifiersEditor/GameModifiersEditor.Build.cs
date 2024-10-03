// Copyright (c) 2024 Anoho All rights reserved.

using UnrealBuildTool;

public class GameModifiersEditor : ModuleRules
{
	public GameModifiersEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[] 
			{
				"Core", 
				"CoreUObject", 
				"Engine",
				"InputCore",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AssetDefinition",
				"AssetTools",
				"GameModifiers",
				"PluginBrowser",
				"Projects",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"UnrealEd",
			}
		);
	}
}
