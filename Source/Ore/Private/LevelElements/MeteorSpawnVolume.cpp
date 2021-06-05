// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/MeteorSpawnVolume.h"
#include "Components/BoxComponent.h"

AMeteorSpawnVolume::AMeteorSpawnVolume()
{
	VolumeShape = CreateDefaultSubobject<UBoxComponent>(TEXT("MeteorSpawn"));
	SetRootComponent(VolumeShape);
	Cast<UBoxComponent>(VolumeShape)->SetBoxExtent(FVector(10000.f, 10000.f, 100.f));
}
