// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersActorRegistry.h"

void UGameModifiersActorRegistry::GetComponentClassesForActorClass(const TSubclassOf<AActor> InActorClass, TArray<TSubclassOf<UActorComponent>>& OutComponentClasses) const
{
	OutComponentClasses.Empty();

	const TArray<TSubclassOf<UActorComponent>>* RegisteredComponentClasses = RegisteredComponentClassesForActorClasses.Find(InActorClass);

	if (!RegisteredComponentClasses)
	{
		return;
	}

	for (const TSubclassOf<UActorComponent>& Component : *RegisteredComponentClasses)
	{
		OutComponentClasses.Emplace(Component);
	}
}

void UGameModifiersActorRegistry::GetAbilitySetsForActorClass(const TSubclassOf<AActor> InActorClass, TArray<const UGameModifiersAbilitySet*>& OutAbilitySets) const
{
	OutAbilitySets.Empty();

	const TArray<const UGameModifiersAbilitySet*>* RegisteredAbilitySets = RegisteredAbilitySetsForActorClasses.Find(InActorClass);

	if (!RegisteredAbilitySets)
	{
		return;
	}

	for (const UGameModifiersAbilitySet* GameplayAbility : *RegisteredAbilitySets)
	{
		OutAbilitySets.Emplace(GameplayAbility);
	}
}

TSubclassOf<AActor> UGameModifiersActorRegistry::GetOverrideForActorClass(const TSubclassOf<AActor> InOrigin) const
{
	if (!RegisteredOverridesForActorClasses.Contains(InOrigin))
	{
		return InOrigin;
	}

	return *RegisteredOverridesForActorClasses.Find(InOrigin);
}

void UGameModifiersActorRegistry::RegisterComponentClassForActorClass(const TSubclassOf<AActor> InActorClass, const TSubclassOf<UActorComponent> InComponentClass)
{
	TArray<TSubclassOf<UActorComponent>>& ComponentClasses = RegisteredComponentClassesForActorClasses.FindOrAdd(InActorClass);

	if (!ComponentClasses.Contains(InComponentClass))
	{
		ComponentClasses.Emplace(InComponentClass);
	}
}

void UGameModifiersActorRegistry::RegisterAbilitySetForActorClass(const TSubclassOf<AActor> InActorClass, const UGameModifiersAbilitySet* InAbilitySet)
{
	TArray<const UGameModifiersAbilitySet*>& GameplayAbilityClasses = RegisteredAbilitySetsForActorClasses.FindOrAdd(InActorClass);

	if (!GameplayAbilityClasses.Contains(InAbilitySet))
	{
		GameplayAbilityClasses.Emplace(InAbilitySet);
	}
}

void UGameModifiersActorRegistry::RegisterOverrideForActorClass(const TSubclassOf<AActor> InOrigin, const TSubclassOf<AActor> InOverride)
{
	RegisteredOverridesForActorClasses.Emplace(InOrigin, InOverride);
}

void UGameModifiersActorRegistry::UnregisterComponentClassForActorClass(const TSubclassOf<AActor> InActorClass, const TSubclassOf<UActorComponent> InComponentClass)
{
	TArray<TSubclassOf<UActorComponent>>* ComponentClasses = RegisteredComponentClassesForActorClasses.Find(InActorClass);

	if (!ComponentClasses)
	{
		return;
	}

	ComponentClasses->Remove(InComponentClass);
}

void UGameModifiersActorRegistry::UnregisterAbilitySetForActorClass(const TSubclassOf<AActor> InActorClass, const UGameModifiersAbilitySet* InAbilitySet)
{
	TArray<const UGameModifiersAbilitySet*>* AbilitySets = RegisteredAbilitySetsForActorClasses.Find(InActorClass);

	if (!AbilitySets)
	{
		return;
	}

	AbilitySets->Remove(InAbilitySet);
}

void UGameModifiersActorRegistry::UnregisterOverrideForActorClass(const TSubclassOf<AActor> InOrigin)
{
	RegisteredOverridesForActorClasses.Remove(InOrigin);
}
