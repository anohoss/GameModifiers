// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in Engine module.
#include "Engine/DataAsset.h"

// Include headers in GameplayAbilities module.
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

#include "GameModifiersAbilitySet.generated.h"

USTRUCT(BlueprintType)
struct GAMEMODIFIERS_API FGameModifiersAbilityEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel{ 1 };

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTagContainer ActivationTags;
};

/**
 * 
 */
UCLASS()
class GAMEMODIFIERS_API UGameModifiersAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:

	void GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject = nullptr) const;

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FGameModifiersAbilityEntry> Abilities;
	
};
