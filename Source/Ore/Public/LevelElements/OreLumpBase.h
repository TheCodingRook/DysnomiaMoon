// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OreInfectionInterface.h"
#include "OreLumpBase.generated.h"

/**
* Custom enumeration type to describe the type of ore mined
*/
UENUM(BlueprintType)
enum class EOreType : uint8
{
	Food UMETA(DisplayName = "Food"),
    Fuel UMETA(DisplayName = "Fuel"),
    Explosive UMETA(DisplayName = "Explosive"),
    Gold UMETA(DisplayName = "Gold"),
	Undefined UMETA(DisplayName = "Undefined")
};

// Forward declarations
class UStaticMeshComponent;

/**
* Custom base class to define the ore type
*/
UCLASS()
class ORE_API AOreLumpBase : public AActor, public IOreInfectionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOreLumpBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	UStaticMeshComponent* GetMesh() const;

	/** IOreInfectionInterface */
	virtual void GetInfected_Implementation() override;
	virtual void OnInfectionCleared_Implementation() override;
	/** End: IOreInfectionInterface */
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsInfected() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EOreType OreType;

	// How many units of the resource does each lump provide?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float QuantityPerLump;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bInfected;
	
protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;


};
