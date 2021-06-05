// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OreInfectionInterface.h"
#include "OreMineBase.generated.h"

// Forward declarations
class AOrePipeline;
class AInfectionSpawnVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInfectionWasCleared);

UCLASS()
class ORE_API AOreMineBase : public AActor, public IOreInfectionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOreMineBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetInfectionState(bool bInfectionState);

	bool IsInfected() const;

	/** IOreInfectionInterface */
	virtual void GetInfected_Implementation() override;
	virtual void OnInfectionCleared_Implementation() override;
	/** End: IOreInfectionInterface */

	UFUNCTION(BlueprintCallable)
    void OnMineDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser );
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInfected;

	// List of connected pipeline(s)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AOrePipeline*> Pipelines;

	// Hold a reference to an 'infection spawner' volume
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AInfectionSpawnVolume* InfectionSpawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintAssignable)
	FInfectionWasCleared InfectionWasCleared;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText MineName;

};
