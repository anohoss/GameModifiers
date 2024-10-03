// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in PluginBrowser module.
#include "IPluginWizardDefinition.h"

/**
 * GameModifierのプラグインを作成するウィザードの定義
 */
class FGameModifiersPluginWizardDefinition : public IPluginWizardDefinition
{
public:

	FGameModifiersPluginWizardDefinition();

public:
	
	// Begin IPluginWizardDefinition interface

	const TArray<TSharedRef<FPluginTemplateDescription>>& GetTemplatesSource() const override;

	void OnTemplateSelectionChanged(TSharedPtr<FPluginTemplateDescription> InSelectedItem, ESelectInfo::Type SelectInfo) override;

	bool HasValidTemplateSelection() const override;

	TSharedPtr<FPluginTemplateDescription> GetSelectedTemplate() const override;

	void ClearTemplateSelection() override;

	bool CanShowOnStartup() const override;

	/**選択中のテンプレートがコードを生成する場合、True*/
	bool HasModules() const override;

	bool IsMod() const override;

	void OnShowOnStartupCheckboxChanged(ECheckBoxState CheckBoxState) override;

	ECheckBoxState GetShowOnStartupCheckBoxState() const override;

	TSharedPtr<class SWidget> GetCustomHeaderWidget() override;

	FText GetInstructions() const override;

	bool GetPluginIconPath(FString& OutIconPath) const override;

	EHostType::Type GetPluginModuleDescriptor() const override;

	ELoadingPhase::Type GetPluginLoadingPhase() const override;

	bool GetTemplateIconPath(TSharedRef<FPluginTemplateDescription> InTemplate, FString& OutIconPath) const override;

	FString GetPluginFolderPath() const override;

	TArray<FString> GetFoldersForSelection() const override;

	void PluginCreated(const FString& PluginName, bool bWasSuccessful) const override;

	// End IPluginWizardDefinition interface

private:

	/*プラグインの作成に利用可能なテンプレート*/
	TArray<TSharedRef<FPluginTemplateDescription>> PluginTemplates;

	TSharedPtr<FPluginTemplateDescription> SelectedTemplate;

	FString PluginBaseDir;
};
