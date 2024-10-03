// Copyright (c) 2024 Anoho All rights reserved.

#include "AbilitySystem/GameModifiersAbilitySet.h"

void UGameModifiersAbilitySet::GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent, UObject* SourceObject) const
{
	check(AbilitySystemComponent);

	// Protega は Server-Client で実行されるため、Client では実行されない
	if (!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		return;
	}

	for (const FGameModifiersAbilityEntry& Ability : Abilities)
	{
		FGameplayAbilitySpec NewAbilitySpec{ Ability.AbilityClass, Ability.AbilityLevel, INDEX_NONE, SourceObject };
		NewAbilitySpec.DynamicAbilityTags.AppendTags(Ability.ActivationTags);

		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(NewAbilitySpec);
	}
}
