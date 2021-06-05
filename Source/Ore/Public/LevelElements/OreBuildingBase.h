// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OreInfectionInterface.h"
#include "LevelElements/OreLumpBase.h"
#include "OreBuildingBase.generated.h"

// Forward declarations
class UBillboardComponent;
class UCapsuleComponent;
//enum class EOreType : uint8;
class USwitchInteraction;
class ARocketShipBase;

/**
* Custom enumeration type to explain the type of building in the game
*/
UENUM(BlueprintType)
enum class ELocationType : uint8
{
	PowerPlant UMETA(DisplayName = "Power plant"),
    FoodProcessingPlant UMETA(DisplayName = "Food processing plant"),
    Armory UMETA(DisplayName = "Armory"),
    GoldWarehouse UMETA(DisplayName = "Gold warehouse"),
    AirDefenseSystem UMETA(DisplayName = "Air defense system"),
};

USTRUCT(BlueprintType)
struct FResource
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOreType ResourceType;

	// Current quantity of the resource in this building
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Quantity;

	// How much resource this building spends per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpendPerSecond;
};

UCLASS()
class ORE_API AOreBuildingBase : public AActor, public IOreInfectionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOreBuildingBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsInfected() const;

	bool IsPoweredOn() const;

	bool IsSwitchedOn() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Infection")
	void OnBuildingInfected();

	UFUNCTION(BlueprintCallable, Category = "Operations")
	void SetPower(bool InPowerState);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Operations")
	void OnSwitchToggled(bool InSwitchState);

	UFUNCTION(BlueprintCallable, Category = "Operations")
	void AcceptResourceFromPipeline(EOreType InResourceType, float InQuantity);

	/** IOreInfectionInterface */
	virtual void GetInfected_Implementation() override;
	virtual void OnInfectionCleared_Implementation() override;
	/** End: IOreInfectionInterface */

	// Returns true if all resource quantities are positive
	UFUNCTION(BlueprintCallable)
	bool CheckResources();

	UFUNCTION(BlueprintPure)
	ELocationType GetLocationType() const;

	UFUNCTION(BlueprintCallable)
    void OnBuildingDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location Details")
	ELocationType LocationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location Details")
	FName LocationName;

	UPROPERTY(VisibleAnywhere)
	UBillboardComponent* Sprite;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UCapsuleComponent* WidgetCapsule;

	// Used to reset the Widget trigger once the player has stepped out of this volume (i.e. OnActorEndOverlap)
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UCapsuleComponent* WidgetCapsuleReset;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UCapsuleComponent* BlockVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	USwitchInteraction* SwitchInteractionComponent;
	
	// Modify the Camera Boom's arm length
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float ZoomedCameraEffect;

	// Is this building infected?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Infection")
	bool bInfected;

	// Is this building connected to power?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPoweredOn;

	// Are this building's operations switched on?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSwitchedOn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BaseColor_Green = FVector(0.f, 0.1875f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EmissiveColor_Green = FVector(0.011f, 0.77f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BaseColor_Red = FVector(0.1f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EmissiveColor_Red = FVector(1.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BaseColor_Amber = FVector(.35f, .08f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EmissiveColor_Amber = FVector(1.f, .7f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "LocationType == ELocationType::PowerPlant"))
	TArray<AOreBuildingBase*> ConnectedInfrastructure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResource> Resources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 2000;

	// Only for GoldWarehouse
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ARocketShipBase* RocketShip;
};
