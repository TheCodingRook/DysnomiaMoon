// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"

#include "OreMineBase.h"
#include "LevelElements/SpawnVolumeBase.h"
#include "InfectionSpawnVolume.generated.h"

// Forward declarations
class UBillboardComponent;
class AOreMineBase;

/**
 * Custom spawn volume class for spawining some sort of physical representation of an alien infection!
 */
UCLASS()
class ORE_API AInfectionSpawnVolume : public ASpawnVolumeBase
{
	GENERATED_BODY()

public:

	AInfectionSpawnVolume();

	UFUNCTION(BlueprintCallable, Category = "Infection")
	void StartInfection();

	UFUNCTION(BlueprintCallable, Category = "Infection")
    void SpawnBlob();

	void SetMineReference(AOreMineBase* InMineReference);

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UBillboardComponent* Sprite;

public:

	// Count of spawned infectious blobs
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int SpawnCount;
	
private:

	// Timer to control spawns
	FTimerHandle InfectionSpawnTimer;
	
	// Flag to mark the beginning of an infection and the very first spawn of a blob
	bool bFirstSpawn;

	// Reference to the Mine this spawn volume is associated with!
	AOreMineBase* MyMine;
	
};
