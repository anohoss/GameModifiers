// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in Core module.
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

// Include headers in AssetDefinition module.
#include "Misc/AssetCategoryPath.h"

class IGameModifiersEditor : public IModuleInterface
{
public:

	static inline IGameModifiersEditor& Get()
	{
		return FModuleManager::LoadModuleChecked<IGameModifiersEditor>("GameModifiersEditor");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("GameModifiersEditor");
	}

public:

	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const = 0;
};
