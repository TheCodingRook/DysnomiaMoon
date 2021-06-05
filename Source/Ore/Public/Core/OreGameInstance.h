// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OreGameInstance.generated.h"

// Forward declarations
class UInteractionComponentBase;

/**
 * The custom GameInstance class that defines the various modes and settings for the game, across various levels and maps
 */
UCLASS()
class ORE_API UOreGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Interactions")
    UInteractionComponentBase* GetLatestInteraction();

	UFUNCTION(BlueprintCallable, Category = "Interactions")
    void PushNewInteraction(class UInteractionComponentBase* NewInteraction);

	UFUNCTION(BlueprintCallable, Category = "Interactions")
    void PopInteraction();

private:

	UInteractionComponentBase* LatestInteraction;
	
};
