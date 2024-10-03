// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersLevelBlueprintLibrary.h"

// Include headers in Engine module.
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

// Include headers in GameModifiers module.
#include "GameModifiersLevelRegistry.h"

ULevelStreamingDynamic* UGameModifiersLevelBlueprintLibrary::LoadLevelInstance(UObject* WorldContextObject, FName LevelName, FVector Location, FRotator Rotation, bool& bOutSuccess, const FString& OptionalLevelNameOverride, const TSubclassOf<ULevelStreamingDynamic> OptionalLevelStreamingClass, const bool bLoadAsTempPackage)
{
	TObjectPtr<UGameModifiersLevelRegistry> LevelRegistry = GEngine->GetEngineSubsystem<UGameModifiersLevelRegistry>();

	if (LevelRegistry)
	{
		FGameModifiersLevelOverride LevelOverride = LevelRegistry->GetLevelOverrideByName(LevelName);

		return ULevelStreamingDynamic::LoadLevelInstance(WorldContextObject, LevelOverride.GetLongPackageNameStr(), Location, Rotation, bOutSuccess, OptionalLevelNameOverride, OptionalLevelStreamingClass, bLoadAsTempPackage);
	}
	else
	{
		return ULevelStreamingDynamic::LoadLevelInstance(WorldContextObject, LevelName.ToString(), Location, Rotation, bOutSuccess, OptionalLevelNameOverride, OptionalLevelStreamingClass, bLoadAsTempPackage);
	}
}

void UGameModifiersLevelBlueprintLibrary::OpenLevel(UObject* WorldContextObject, FName LevelName, bool bAbsolute, FString Options)
{
	TObjectPtr<UGameModifiersLevelRegistry> LevelRegistry = GEngine->GetEngineSubsystem<UGameModifiersLevelRegistry>();

	if (LevelRegistry)
	{
		FGameModifiersLevelOverride LevelOverride = LevelRegistry->GetLevelOverrideByName(LevelName);

		UGameplayStatics::OpenLevel(WorldContextObject, LevelOverride.LongPackageName, bAbsolute, Options);
	}
	else
	{
		UGameplayStatics::OpenLevel(WorldContextObject, LevelName, bAbsolute, Options);
	}
}

bool UGameModifiersLevelBlueprintLibrary::UnloadLevelInstance(UObject* WorldContextObject, ULevelStreamingDynamic* LevelToUnload)
{
	if (!LevelToUnload)
	{
		return false;
	}

	LevelToUnload->SetShouldBeLoaded(false);
	LevelToUnload->SetShouldBeVisible(false);
	LevelToUnload->SetIsRequestingUnloadAndRemoval(false);

	return true;
}
