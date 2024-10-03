// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersPluginWizardDefinition.h"

// Include headers in GameModifiersEditor module.
#include "GameModifiersPluginTemplateDescription.h"
#include "Features/IGameModifiersEditorPluginsFeature.h"

#define LOCTEXT_NAMESPACE "GameModifiersPluginWizard"

FGameModifiersPluginWizardDefinition::FGameModifiersPluginWizardDefinition()
{
	const TArray<TSharedRef<FPluginTemplateDescription>>& RegisteredPluginTemplates = IGameModifiersEditorPluginsFeature::Get().GetRegisteredPluginTemplates();

	for (const TSharedRef<FPluginTemplateDescription>& Template : RegisteredPluginTemplates)
	{
		PluginTemplates.Emplace(Template);
	}
}

const TArray<TSharedRef<FPluginTemplateDescription>>& FGameModifiersPluginWizardDefinition::GetTemplatesSource() const
{
	return PluginTemplates;
}

void FGameModifiersPluginWizardDefinition::OnTemplateSelectionChanged(TSharedPtr<FPluginTemplateDescription> InSelectedItem, ESelectInfo::Type SelectInfo)
{
	SelectedTemplate = InSelectedItem;
}

bool FGameModifiersPluginWizardDefinition::HasValidTemplateSelection() const
{
	// テンプレートが選択されていればOK
	return SelectedTemplate.IsValid();
}

TSharedPtr<FPluginTemplateDescription> FGameModifiersPluginWizardDefinition::GetSelectedTemplate() const
{
	return SelectedTemplate;
}

void FGameModifiersPluginWizardDefinition::ClearTemplateSelection()
{
	SelectedTemplate.Reset();
}

bool FGameModifiersPluginWizardDefinition::CanShowOnStartup() const
{
	return false;
}

bool FGameModifiersPluginWizardDefinition::HasModules() const
{
	bool bHasModules = SelectedTemplate.IsValid()
		&& FPaths::DirectoryExists(SelectedTemplate->OnDiskPath / TEXT("Source"));

	return bHasModules;
}

bool FGameModifiersPluginWizardDefinition::IsMod() const
{
	// GameModfierのプラグインは全てMODとして扱う
	return true;
}

void FGameModifiersPluginWizardDefinition::OnShowOnStartupCheckboxChanged(ECheckBoxState CheckBoxState) {}

ECheckBoxState FGameModifiersPluginWizardDefinition::GetShowOnStartupCheckBoxState() const
{
	return ECheckBoxState::Unchecked;
}

TSharedPtr<class SWidget> FGameModifiersPluginWizardDefinition::GetCustomHeaderWidget()
{
	return nullptr;
}

FText FGameModifiersPluginWizardDefinition::GetInstructions() const
{
	return LOCTEXT("GameModifierWizardInstructions", "Give your new GameModifier package a name and Click 'Create Mod' to make a new GameModifier package.");
}

bool FGameModifiersPluginWizardDefinition::GetPluginIconPath(FString& OutIconPath) const
{
	if (!SelectedTemplate.IsValid())
	{
		return false;
	}

	FString IconPath = SelectedTemplate->OnDiskPath / TEXT("Resources/Icon128.png");

	if (!FPaths::FileExists(IconPath))
	{
		return false;
	}

	OutIconPath = IconPath;

	return true;
}

EHostType::Type FGameModifiersPluginWizardDefinition::GetPluginModuleDescriptor() const
{
	EHostType::Type ModuleDescriptorType = EHostType::Runtime;

	if (SelectedTemplate.IsValid())
	{
		ModuleDescriptorType = SelectedTemplate->ModuleDescriptorType;
	}

	return ModuleDescriptorType;
}

ELoadingPhase::Type FGameModifiersPluginWizardDefinition::GetPluginLoadingPhase() const
{
	ELoadingPhase::Type Phase = ELoadingPhase::Default;

	if (SelectedTemplate.IsValid())
	{
		Phase = SelectedTemplate->LoadingPhase;
	}

	return Phase;
}

bool FGameModifiersPluginWizardDefinition::GetTemplateIconPath(TSharedRef<FPluginTemplateDescription> InTemplate, FString& OutIconPath) const
{
	FString IconPath = InTemplate->OnDiskPath / TEXT("Resources/Icon128.png");

	if (!FPaths::FileExists(IconPath))
	{
		return false;
	}

	OutIconPath = IconPath;

	return true;
}

FString FGameModifiersPluginWizardDefinition::GetPluginFolderPath() const
{
	return SelectedTemplate->OnDiskPath;
}

TArray<FString> FGameModifiersPluginWizardDefinition::GetFoldersForSelection() const
{
	TArray<FString> SelectedFolders;

	if (SelectedTemplate.IsValid())
	{
		SelectedFolders.Add(SelectedTemplate->OnDiskPath);
	}

	return SelectedFolders;
}

void FGameModifiersPluginWizardDefinition::PluginCreated(const FString& PluginName, bool bWasSuccessful) const {}

#undef LOCTEXT_NAMESPACE // GameModifiersPluginWizard
