// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in Engine module.
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/LevelStreamingDynamic.h"

#include "GameModifiersLevelBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMODIFIERS_API UGameModifiersLevelBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static ULevelStreamingDynamic* LoadLevelInstance(UObject* WorldContextObject, FName LevelName, FVector Location, FRotator Rotation, bool& bOutSuccess, const FString& OptionalLevelNameOverride = TEXT(""), const TSubclassOf<ULevelStreamingDynamic> OptionalLevelStreamingClass = nullptr, const bool bLoadAsTempPackage = false);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void OpenLevel(UObject* WorldContextObject, FName LevelName, bool bAbsolute = true, FString Options = TEXT(""));

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static bool UnloadLevelInstance(UObject* WorldContextObject, ULevelStreamingDynamic* LevelStreaming);
};
