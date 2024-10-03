// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersActorBlueprintLibrary.h"

// Include headers in Engine module.
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

// Include headers in GameModifier module.
#include "GameModifiersActorRegistry.h"

// Include headers in GameplayAbilities module.
#include "AbilitySystemComponent.h"

AActor* UGameModifiersActorBlueprintLibrary::SpawnActor(UObject* WorldContextObject, const TSubclassOf<AActor>& InActorClass)
{
	TObjectPtr<UWorld> World = WorldContextObject->GetWorld();

	if (!World)
	{
		return nullptr;
	}

	TObjectPtr<UGameModifiersActorRegistry> ActorRegistry = GEngine->GetEngineSubsystem<UGameModifiersActorRegistry>();

	if (ActorRegistry)
	{
		const TSubclassOf<AActor>& NewActorClass = ActorRegistry->GetOverrideForActorClass(InActorClass);

		TObjectPtr<AActor> NewActor = World->SpawnActor(NewActorClass);

		if (!NewActor)
		{
			return nullptr;
		}

		TObjectPtr<UAbilitySystemComponent> Asc = NewActor->GetComponentByClass<UAbilitySystemComponent>();

		if (Asc)
		{
			TArray<const UGameModifiersAbilitySet*> AbilitySets;

			ActorRegistry->GetAbilitySetsForActorClass(NewActorClass, AbilitySets);

			for (const UGameModifiersAbilitySet* AbilitySet : AbilitySets)
			{
				AbilitySet->GiveAbilities(Asc, /* SourceObject = */ NewActor);
			}
		}

		return NewActor;
	}
	else
	{
		return World->SpawnActor(InActorClass);
	}
}
