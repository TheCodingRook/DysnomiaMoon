// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "LevelElements/OreBuildingBase.h"
#include "GoldWarehouse.generated.h"

// Forward declarations
class ARocketShipBase;

/**
 * 
 */
UCLASS()
class ORE_API AGoldWarehouse : public AOreBuildingBase
{
	GENERATED_BODY()

	public:

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Operations")
	float LoadRocketShip (float InQuantity);
	
};
