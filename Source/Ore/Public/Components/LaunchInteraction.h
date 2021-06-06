// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractionComponentBase.h"
#include "LaunchInteraction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class ORE_API ULaunchInteraction : public UInteractionComponentBase
{
	GENERATED_BODY()

public:

	ULaunchInteraction();
	virtual void ExecuteInteraction(AOrePlayerController* Instigator) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EmergengyLaunch();
};
