// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractionComponentBase.h"
#include "SwitchInteraction.generated.h"

// Forward declarations
class USoundBase;

/**
 * Custom interaction component class to allow the player character to interact with other actors in the world (in this case switch stuff on/off)
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ORE_API USwitchInteraction : public UInteractionComponentBase
{
	GENERATED_BODY()

	public:
	
	USwitchInteraction();
	virtual void ExecuteInteraction(AOrePlayerController* Instigator) override;
	virtual void OnInteractionVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnInteractionVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* SwitchSound;
};
