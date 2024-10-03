// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in GameModifiersEditor module.
#include "Features/GameModifiersEditorFeatures.h"

// Include headers in UnrealEd module.
#include "Features/IPluginsEditorFeature.h"

/**
 * 
 */
class GAMEMODIFIERSEDITOR_API IGameModifiersEditorPluginsFeature : public IModularFeature
{
public:

	static inline IGameModifiersEditorPluginsFeature& Get()
	{
		return IModularFeatures::Get().GetModularFeature<IGameModifiersEditorPluginsFeature>(GameModifiersEditorFeatures::PluginsFeatureType);
	}

	static inline bool IsAvailable()
	{
		return IModularFeatures::Get().IsModularFeatureAvailable(GameModifiersEditorFeatures::PluginsFeatureType);
	}

public:

	virtual const TArray<TSharedRef<FPluginTemplateDescription>>& GetRegisteredPluginTemplates() const = 0;

	virtual void OpenPluginWizard() const = 0;

	virtual void RegisterPluginTemplate(const TSharedRef<FPluginTemplateDescription> InTemplate) = 0;

	virtual void UnregisterPluginTemplate(const TSharedRef<FPluginTemplateDescription> InTemplate) = 0;
};
