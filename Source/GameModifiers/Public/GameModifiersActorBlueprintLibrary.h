// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "Engine/World.h"

// Include headers in Engine module.
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameModifiersActorBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMODIFIERS_API UGameModifiersActorBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", ReturnDisplayName = "Actor"))
	static AActor* SpawnActor(UObject* WorldContextObject, const TSubclassOf<AActor>& InActorClass);
};
