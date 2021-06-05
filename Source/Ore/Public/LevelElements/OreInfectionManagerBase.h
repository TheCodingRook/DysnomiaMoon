// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OreInfectionManagerBase.generated.h"


// Forward declarations
class AOreMineBase;

UCLASS()
class ORE_API AOreInfectionManagerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOreInfectionManagerBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ElapsedTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeUntilNextInfection = 240.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AOreMineBase*> OreMines;
	
public:	

	

};
