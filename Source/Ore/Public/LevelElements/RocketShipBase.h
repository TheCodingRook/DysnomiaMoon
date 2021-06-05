// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OreInfectionInterface.h"
#include "RocketShipBase.generated.h"

UCLASS()
class ORE_API ARocketShipBase : public AActor, public IOreInfectionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocketShipBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* IOreInfectionInterface */
	virtual void GetInfected_Implementation() override;
	virtual void OnInfectionCleared_Implementation() override;
	/* End: IOreInfectionInterface */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Operations")
	float LoadedGold = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxGoldCapacity = 100000;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Operations")
	float LoadedFuel = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFuelRequired = 10000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInLaunchPosition = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Operations")
	float LoadedParasite = 0.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInfected;
	
	
};
