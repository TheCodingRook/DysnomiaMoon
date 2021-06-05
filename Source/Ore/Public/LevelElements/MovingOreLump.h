// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "LevelElements/OreLumpBase.h"
#include "Interfaces/OreActorPoolInterface.h"
#include "MovingOreLump.generated.h"


/**
 * Specialization of the OreLumpBase for moving lumps that traverse a pipeline
 */
UCLASS()
class ORE_API AMovingOreLump : public AOreLumpBase, public IOreActorPoolInterface 
{
	GENERATED_BODY()

	public:

	// IOreActorPoolInterface interface
	virtual void ResetValues_Implementation() override;
	// IOreActorPoolInterface End
	
	
	UPROPERTY(BlueprintReadWrite)
	FVector OriginLocation;

	UPROPERTY(BlueprintReadWrite)
	FVector TargetLocation;

	UPROPERTY(BlueprintReadWrite)
	int CurrentSplineIndex;	
};
