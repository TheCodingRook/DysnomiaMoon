// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OreActorPoolInterface.h"
#include "LevelElements/SpawnVolumeBase.h"
#include "MeteorSpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class ORE_API AMeteorSpawnVolume : public ASpawnVolumeBase, public IOreActorPoolInterface
{
	GENERATED_BODY()

public:

	AMeteorSpawnVolume();

};
