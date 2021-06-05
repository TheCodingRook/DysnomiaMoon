// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OreActorPoolInterface.h"
#include "Meteor.generated.h"

// Forward declarations
class USphereComponent;

UCLASS()
class ORE_API AMeteor : public AActor, public IOreActorPoolInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeteor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* IOreActorPoolInterface */
	virtual void SetupValues_Implementation() override;
	virtual void ResetValues_Implementation() override;
	/* END: IOreActorPoolInterface */
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties

	/** The main root component for the projectile */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	//USceneComponent* DefaultRoot;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeteorMesh;


	UPROPERTY(EditDefaultsOnly)
	USphereComponent* CollisionVolume;

};
