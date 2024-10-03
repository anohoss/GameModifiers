// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in Engine module.
#include "Subsystems/WorldSubsystem.h"

#include "GameModifiersLevelStreamingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMODIFIERS_API UGameModifiersLevelStreamingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	void Initialize(FSubsystemCollectionBase& Collection) override;

	void Deinitialize() override;

private:

	/*
	* UGameModifiersLevelRegistry クラスから LevelName に紐づけられている StreamLevel を読み込む
	*/
	void LoadStreamLevels(const FName& LevelName) const;
};
