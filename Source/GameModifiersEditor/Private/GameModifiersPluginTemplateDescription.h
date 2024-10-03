// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in Projects module.
#include "Interfaces/IPluginManager.h"
#include "PluginDescriptor.h"

// Include headers in UnrealEd module.
#include "Features/IPluginsEditorFeature.h"

/**
 *
 */
struct FGameModifiersPluginTemplateDescription : public FPluginTemplateDescription
{
public:

	FGameModifiersPluginTemplateDescription(FText InName, FText InDescription, FString InOnDiskPath, bool InCanContainContent, EHostType::Type InModuleDescriptorType, ELoadingPhase::Type InLoadingPhase = ELoadingPhase::Default)
		: FPluginTemplateDescription(InName, InDescription, InOnDiskPath, InCanContainContent, InModuleDescriptorType, InLoadingPhase) {};

	~FGameModifiersPluginTemplateDescription() override {};

public:

	// Begin FPluginTemplateDescription interface

	void CustomizeDescriptorBeforeCreation(FPluginDescriptor& Descriptor) override;

	void OnPluginCreated(TSharedPtr<IPlugin> NewPlugin) override;

	// End FPluginTemplateDescription interface
};
