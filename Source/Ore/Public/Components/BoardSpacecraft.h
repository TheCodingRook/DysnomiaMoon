// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractionComponentBase.h"
#include "BoardSpacecraft.generated.h"

/**
 * Custom component class to allow player to interact with a spacecraft and board it.
 */
UCLASS(Blueprintable,  meta=(BlueprintSpawnableComponent))
class ORE_API UBoardSpacecraft : public UInteractionComponentBase
{
	GENERATED_BODY()

protected:

	UBoardSpacecraft();
	virtual void ExecuteInteraction(AOrePlayerController* Instigator) override;
	virtual void StopInteraction(AOrePlayerController* Instigator) override;
};
