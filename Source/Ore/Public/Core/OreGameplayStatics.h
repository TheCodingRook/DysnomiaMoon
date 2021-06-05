// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "OreGameInstance.h"
#include "OreGameMode.h"
#include "OrePlayerController.h"
#include "Pawns/OreCharacter.h"
#include "Pawns/OreCharacter3P.h"
#include "OreGameplayStatics.generated.h"

/**
 * Convenient class for static 'getters' in Project Ore
 */
UCLASS()
class ORE_API UOreGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
    static UOreGameInstance* GetOreGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
    static AOreGameMode* GetOreGameMode(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
    static AOrePlayerController* GetOrePlayerController(const UObject* WorldContextObject);

	// POTENTIALLY UNSAFE TO USE BECAUSE WE SWITCH PAWNS!
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
    static AOreCharacter* GetOreCharacter(const UObject* WorldContextObject);

	// POTENTIALLY UNSAFE TO USE BECAUSE WE SWITCH PAWNS!
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
    static AOreCharacter3P* GetOreCharacter3P(const UObject* WorldContextObject);
	
};
