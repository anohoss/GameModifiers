// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersEditorModule.h"

// Include headers in GameModifiersEditor module.
#include "GameModifiersPluginTemplateDescription.h"

#define LOCTEXT_NAMESPACE "GameModifiersEditorModule"

void FGameModifiersEditorModule::ShutdownModule()
{
	IModularFeatures::Get().UnregisterModularFeature(GameModifiersEditorFeatures::PluginsFeatureType, this);

	UToolMenus::UnregisterOwner(this);
	UToolMenus::UnRegisterStartupCallback(this);

	FGameModifiersEditorStyle::Shutdown();

	FGameModifiersEditorCommands::Unregister();

	UnregisterTabSpawner();
}

void FGameModifiersEditorModule::StartupModule()
{
	FGameModifiersEditorStyle::Initialize();
	FGameModifiersEditorStyle::ReloadTextures();

	FGameModifiersEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	// OpenPluginWizard コマンドに処理を登録する
	PluginCommands->MapAction(
		FGameModifiersEditorCommands::Get().OpenPluginWizard,
		FExecuteAction::CreateRaw(this, &FGameModifiersEditorModule::HandleOpenPluginWizard),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGameModifiersEditorModule::RegisterToolMenus));

	RegisterTabSpawner();

	IModularFeatures::Get().RegisterModularFeature(GameModifiersEditorFeatures::PluginsFeatureType, this);

	RegisterPluginTemplates();	// IGameModifiersEditorPluginsFeature を使うため、RegisterModularFeature よりも前で呼び出さない
}

TConstArrayView<FAssetCategoryPath> FGameModifiersEditorModule::GetAssetCategories() const
{
	static const TArray<FAssetCategoryPath> Categories = {
		FAssetCategoryPath(LOCTEXT("GameModifiersAssetCategory", "Game Modifier"))
	};

	return Categories;
}

void FGameModifiersEditorModule::OpenPluginWizard() const
{
	FGlobalTabmanager::Get()->TryInvokeTab(GameModifiersPluginWizardTabName);
}

void FGameModifiersEditorModule::RegisterPluginTemplate(const TSharedRef<FPluginTemplateDescription> InTemplate)
{
	RegisteredPluginTemplates.Add(InTemplate);
}

void FGameModifiersEditorModule::UnregisterPluginTemplate(const TSharedRef<FPluginTemplateDescription> InTemplate)
{
	RegisteredPluginTemplates.Remove(InTemplate);
}

void FGameModifiersEditorModule::RegisterPluginTemplates() const
{
	if (!IGameModifiersEditorPluginsFeature::IsAvailable())
	{
		return;
	}

	TSharedPtr<IPlugin> GameModifiersPlugin = IPluginManager::Get().FindPlugin(TEXT("GameModifiers"));

	if (!GameModifiersPlugin.IsValid())
	{
		return;
	}

	//auto RegisterPluginTemplate = [](const TSharedRef<FGameModifiersPluginTemplateDescription> InTemplate)
	//	{
	//		IGameModifiersEditorPluginsFeature::Get().RegisterPluginTemplate(InTemplate);
	//	};

	//const FString& PluginBaseDir = GameModifiersPlugin->GetBaseDir();

	//// Add content-only template.
	//{
	//	const FText TemplateName = LOCTEXT("ContentOnlyTemplateName", "ContentOnly");
	//	const FText TemplateDescription = LOCTEXT("ContentOnlyTemplateDescription", "Create a blank plugin that can only contain content.");
	//	const FString TemplateOnDiskPath = PluginBaseDir / TEXT("Templates/ContentOnly");
	//	const bool TemplateCanContainContent = true;

	//	TSharedRef<FGameModifiersPluginTemplateDescription> Template = MakeShareable(
	//		new FGameModifiersPluginTemplateDescription(
	//			TemplateName,
	//			TemplateDescription,
	//			TemplateOnDiskPath,
	//			TemplateCanContainContent,
	//			EHostType::Runtime,
	//			ELoadingPhase::Default)
	//	);

	//	RegisterPluginTemplate(Template);
	//}
}

void FGameModifiersEditorModule::RegisterTabSpawner()
{
	// GameModifiersPluginWizard の生成処理を登録する
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(GameModifiersPluginWizardTabName, FOnSpawnTab::CreateRaw(this, &FGameModifiersEditorModule::HandleSpawnPluginWizardTab))
		.SetDisplayName(LOCTEXT("GameModifiersPluginWizardTabTitle", "Game Modifier Plugin Wizard"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FGameModifiersEditorModule::RegisterToolMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	if (UToolMenu* LevelEditorToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar"))
	{
		// ToolMenus に OpenPluginWizard を登録する
		FToolMenuSection& Section = LevelEditorToolbarMenu->FindOrAddSection("GameModifiers");
		FToolMenuEntry& Entry = Section.AddEntry(
			FToolMenuEntry::InitToolBarButton(
				FGameModifiersEditorCommands::Get().OpenPluginWizard,
				TAttribute<FText>(),
				TAttribute<FText>(),
				FSlateIcon(FGameModifiersEditorStyle::GetStyleSetName(), "OpenGameModifiersPluginWizard")));

		Entry.SetCommandList(PluginCommands);
	}
}

void FGameModifiersEditorModule::HandleOpenPluginWizard() const
{
	OpenPluginWizard();
}

TSharedRef<SDockTab> FGameModifiersEditorModule::HandleSpawnPluginWizardTab(const FSpawnTabArgs& SpawnTabArgs)
{
	check(IPluginBrowser::IsAvailable());

	return IPluginBrowser::Get().SpawnPluginCreatorTab(SpawnTabArgs, MakeShared<FGameModifiersPluginWizardDefinition>());
}

void FGameModifiersEditorModule::UnregisterTabSpawner()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GameModifiersPluginWizardTabName);
}

#undef LOCTEXT_NAMESPACE // GameModifiersEditorModule

IMPLEMENT_MODULE(FGameModifiersEditorModule, GameModifiersEditor);
