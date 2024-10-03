// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersEditorStyle.h"

// Include headers in Engine module.
#include "Slate/SlateGameResources.h"

// Include headers in Projects module.
#include "Interfaces/IPluginManager.h"

// Include headers in Slate module.
#include "Framework/Application/SlateApplication.h"

// Include headers in SlateCore module.
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir StyleSet->RootToContentDir

static const FName GameModifiersEditorStyleSetName(TEXT("GameModifiersEditorStyle"));

TSharedPtr<FSlateStyleSet> FGameModifiersEditorStyle::StyleInstance = nullptr;

void FGameModifiersEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FGameModifiersEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FGameModifiersEditorStyle::GetStyleSetName()
{
	return GameModifiersEditorStyleSetName;
}

const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FGameModifiersEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > StyleSet = MakeShareable(new FSlateStyleSet(GameModifiersEditorStyleSetName));

	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin("GameModifiers")->GetBaseDir() / TEXT("Resources"));

	StyleSet->Set("OpenGameModifiersPluginWizard", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return StyleSet;
}

void FGameModifiersEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FGameModifiersEditorStyle::Get()
{
	return *StyleInstance;
}
