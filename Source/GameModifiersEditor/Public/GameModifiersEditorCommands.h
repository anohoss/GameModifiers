// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in Slate module.
#include "Framework/Commands/Commands.h"

// Include headers in GameModifiersEditor module.
#include "GameModifiersEditorStyle.h"

class FGameModifiersEditorCommands : public TCommands<FGameModifiersEditorCommands>
{
public:

	FGameModifiersEditorCommands()
		: TCommands<FGameModifiersEditorCommands>(TEXT("GameModifiersEditor"), NSLOCTEXT("GameModifiersEditorCommands", "GameModifiersEditor", "Game Modifier Editor"), NAME_None, FGameModifiersEditorStyle::GetStyleSetName())
	{
	}

	// Begin TCommands<> interface
	virtual void RegisterCommands() override;

public:

	TSharedPtr< FUICommandInfo > OpenPluginWizard;
};
