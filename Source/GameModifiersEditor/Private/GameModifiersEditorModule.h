// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in GameModifierEditor module.
#include "Features/IGameModifiersEditorPluginsFeature.h"
#include "GameModifiersEditorCommands.h"
#include "GameModifiersEditorStyle.h"
#include "GameModifiersPluginWizardDefinition.h"
#include "IGameModifiersEditor.h"

// Include headers in PluginBrowser module.
#include "IPluginBrowser.h"

// Include headers in Slate module.
#include "Framework/Commands/UICommandList.h"

// Include headers in ToolMenus module.
#include "ToolMenus.h"

static const FName GameModifiersPluginWizardTabName("GameModifiers Plugin Wizard");

#define LOCTEXT_NAMESPACE "GameModifiersEditorModule"

class FGameModifiersEditorModule : public IGameModifiersEditor, public IGameModifiersEditorPluginsFeature
{
public:

	// Begin IModuleInterface interface

	void ShutdownModule() override;
	
	void StartupModule() override;

	// End IModuleInterface interface

	// Begin IGameModifiersEditor interface

	TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;

	// End IGameModifiersEditor interface

	// Begin IGameModifiersEditorPluginsFeature interface

	const TArray<TSharedRef<FPluginTemplateDescription>>& GetRegisteredPluginTemplates() const override { return RegisteredPluginTemplates; }

	/*GameModifiersPluginWizardを開く*/
	void OpenPluginWizard() const override;

	void RegisterPluginTemplate(const TSharedRef<FPluginTemplateDescription> InTemplate) override;

	void UnregisterPluginTemplate(const TSharedRef<FPluginTemplateDescription> InTemplate) override;

	// End IGameModifiersEditorPluginsFeature interface

private:

	void RegisterPluginTemplates() const;

	void RegisterTabSpawner();

	void RegisterToolMenus();

	void HandleOpenPluginWizard() const;

	/*GameModifiersPluginWizardを生成する*/
	TSharedRef<SDockTab> HandleSpawnPluginWizardTab(const FSpawnTabArgs& SpawnTabArgs);

	void UnregisterTabSpawner();

private:

	TSharedPtr<FUICommandList> PluginCommands;

	TArray<TSharedRef<FPluginTemplateDescription>> RegisteredPluginTemplates;
};
