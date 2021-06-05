// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/SpawnVolumeBase.h"

// Sets default values
ASpawnVolumeBase::ASpawnVolumeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnVolumeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolumeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

