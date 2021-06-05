// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/OreFiringComponent.h"
#include "OreBombingComponent.generated.h"

/**
 * 
 */
UCLASS()
class ORE_API UOreBombingComponent : public UOreFiringComponent
{
	GENERATED_BODY()

	public:

	virtual void FireWeapon() override;

	// This is used for the second missile launcher of the spacecraft (fighterjet)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AOreWeapon* EquippedWeapon2;
};
