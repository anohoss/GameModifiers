// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersPluginTemplateDescription.h"

// Include headers in AssetTools module.
#include "IAssetTools.h"

// Include headers in UnrealEd module.
#include "FileHelpers.h"

void FGameModifiersPluginTemplateDescription::CustomizeDescriptorBeforeCreation(FPluginDescriptor& Descriptor)
{
	Descriptor.Category = TEXT("Game Modifiers");
	Descriptor.bNoCode = true;	// GameModifiers プラグインは pak としてパッケージ化するため、コードを含まない
}

void FGameModifiersPluginTemplateDescription::OnPluginCreated(TSharedPtr<IPlugin> NewPlugin)
{
	if (NewPlugin->CanContainContent())
	{
		const FString& PluginName = NewPlugin->GetName();
		FString PluginContentDir = NewPlugin->GetMountedAssetPath();
	}
}
