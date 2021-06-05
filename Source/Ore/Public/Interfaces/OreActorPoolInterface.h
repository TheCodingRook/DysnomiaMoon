// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OreActorPoolInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOreActorPoolInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ORE_API IOreActorPoolInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ActorPool")
    void SetupValues();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ActorPool")
	void ResetValues();
};
