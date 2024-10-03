// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersActorSpawner.h"

// Sets default values
AGameModifiersActorSpawner::AGameModifiersActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameModifiersActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameModifiersActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

