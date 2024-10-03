// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersEditorCommands.h"

#define LOCTEXT_NAMESPACE "FGameModifiersEditorModule"

void FGameModifiersEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWizard, "OpenGameModifiersPluginWizard", "Open Game Modifiers Plugin Wizard", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
