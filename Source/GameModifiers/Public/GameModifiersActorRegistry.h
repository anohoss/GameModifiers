// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in Engine module.
#include "Subsystems/EngineSubsystem.h"

// Include headers in GameplayAbilities module.
#include "Abilities/GameplayAbility.h"

// Include headers in GameModifiers module.
#include "AbilitySystem/GameModifiersAbilitySet.h"

#include "GameModifiersActorRegistry.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMODIFIERS_API UGameModifiersActorRegistry : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	/*
	* アクタに関連付けられたコンポーネントのクラスを取得する
	*/
	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Actor")
	void GetComponentClassesForActorClass(const TSubclassOf<AActor> InActorClass, TArray<TSubclassOf<UActorComponent>>& OutComponentClasses) const;

	/*
	* アクタに関連付けられたゲームプレイアビリティのクラスを取得する
	*/
	void GetAbilitySetsForActorClass(const TSubclassOf<AActor> InActorClass, TArray<const UGameModifiersAbilitySet*>& OutAbilitySets) const;

	/*
	* アクタに登録されているオーバーライドを取得する
	*/
	UFUNCTION(BlueprintCallable, Category="GameModifiers|Actor")
	TSubclassOf<AActor> GetOverrideForActorClass(const TSubclassOf<AActor> InOrigin) const;

	/*
	* アクタに対して追加するコンポーネントのクラスを登録する
	*/
	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Actor")
	void RegisterComponentClassForActorClass(const TSubclassOf<AActor> InActorClass, const TSubclassOf<UActorComponent> InComponentClass);

	/*
	* アクタに対して追加するゲームプレイアビリティのクラスを登録する
	*/
	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Actor")
	void RegisterAbilitySetForActorClass(const TSubclassOf<AActor> InActorClass, const UGameModifiersAbilitySet* InAbilitySet);

	/*
	* アクタをオーバーライドするクラスを登録する
	*/
	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Actor")
	void RegisterOverrideForActorClass(const TSubclassOf<AActor> InOrigin, const TSubclassOf<AActor> InOverride);

	/*
	* 指定したコンポーネントの登録を削除する
	*/
	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Actor")
	void UnregisterComponentClassForActorClass(const TSubclassOf<AActor> InActorClass, const TSubclassOf<UActorComponent> ComponentClass);

	/*
	* 指定したゲームプレイアビリティの登録を削除する
	*/
	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Actor")
	void UnregisterAbilitySetForActorClass(const TSubclassOf<AActor> InActorClass, const UGameModifiersAbilitySet* InAbilitySet);

	/*
	* 指定したアクタのオーバーライドを削除する
	*/
	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Actor")
	void UnregisterOverrideForActorClass(const TSubclassOf<AActor> InOrigin);

private:

	TMap<TSubclassOf<AActor>, TSubclassOf<AActor>> RegisteredOverridesForActorClasses;

	TMap<TSubclassOf<AActor>, TArray<TSubclassOf<UActorComponent>>> RegisteredComponentClassesForActorClasses;

	TMap<TSubclassOf<AActor>, TArray<const UGameModifiersAbilitySet*>> RegisteredAbilitySetsForActorClasses;
};
