// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolumeBase.generated.h"

UCLASS()
class ORE_API ASpawnVolumeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolumeBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> SpawnActorClass;

	// If false, spawning happens at random intervals
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bFixedFrequency = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bFixedFrequency == true"))
	float SpawnFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bFixedFrequency == false"))
	float MinSpawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bFixedFrequency == false"))
	float MaxSpawnDelay;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UShapeComponent* VolumeShape;
	
};
