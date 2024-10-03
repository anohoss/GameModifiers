// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersLevelStreamingSubsystem.h"

// Include headers in Engine module.
#include "Kismet/GameplayStatics.h"

// Include headers in GameModifiers module.
#include "GameModifiersLevelRegistry.h"
#include "GameModifiersLevelBlueprintLibrary.h"

void UGameModifiersLevelStreamingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	TObjectPtr<UWorld> World = GetWorld();

	if (World)
	{
		TObjectPtr<ULevel> PersistentLevel = World->PersistentLevel;

		if (PersistentLevel)
		{
			FAssetData PersistentLevelAssetData{ PersistentLevel };

			FString PieRemovedPackageNameStr = UWorld::RemovePIEPrefix(PersistentLevelAssetData.PackageName.ToString());

			LoadStreamLevels(FName(PieRemovedPackageNameStr));
		}
	}
}

void UGameModifiersLevelStreamingSubsystem::Deinitialize()
{
}


void UGameModifiersLevelStreamingSubsystem::LoadStreamLevels(const FName& LevelName) const
{
	UGameModifiersLevelRegistry* LevelRegistry = GEngine->GetEngineSubsystem<UGameModifiersLevelRegistry>();

	if (LevelRegistry)
	{
		TArray<FGameModifiersStreamLevel> StreamLevels;

		LevelRegistry->GetStreamLevelsByName(LevelName, StreamLevels);

		for (const FGameModifiersStreamLevel& StreamLevel : StreamLevels)
		{
			UObject* WorldContextObject = GetWorld();
			FName LevelNameToLoad = StreamLevel.LongPackageName;
			FVector Location{};
			FRotator Rotation{};
			bool bOutSuccess;

			UGameModifiersLevelBlueprintLibrary::LoadLevelInstance(WorldContextObject, LevelNameToLoad, Location, Rotation, bOutSuccess);
		}
	}
}
