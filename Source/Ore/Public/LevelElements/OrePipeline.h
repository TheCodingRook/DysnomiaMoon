// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/OreActorPoolComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OreInfectionInterface.h"
#include "OrePipeline.generated.h"

// Forward declarations
class USplineComponent;
class UBillboardComponent;
class AMovingOreLump;
class UInstancedStaticMeshComponent;
class AOreActorPoolComponent;
enum class EOreType : uint8;
class AOreBuildingBase;
class USwitchInteraction;

/**
 * Custom class defining a pipeline that takes ore from mine deposits to its final destination
 */
UCLASS()
class ORE_API AOrePipeline : public AActor, public IOreInfectionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrePipeline();

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void CreditBuildingWithResource(EOreType InResourceType, float InCredit);

	/** IOreInfectionInterface */
	virtual void GetInfected_Implementation() override;
	virtual void OnInfectionCleared_Implementation() override;
	/**~ End: IOreInfectionInterface */

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsInfected() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsSwitchedOn() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Operations")
    void OnSwitchToggled(bool InSwitchState);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite)
	bool bStartFlow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> OreClass;

	UPROPERTY(BlueprintReadWrite)
	float ElapsedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FlowRate;

	UFUNCTION(BlueprintCallable)
    void OnPipelineDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser );
	
protected:

	UPROPERTY(EditDefaultsOnly)
	UBillboardComponent* Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* SplineComponent;

	UPROPERTY(BlueprintReadWrite)
	TArray<UInstancedStaticMeshComponent*> InstancedMeshes;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	USwitchInteraction* SwitchInteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AMovingOreLump*> MovingOreLumps;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UOreActorPoolComponent* OreActorPool;

	// Default multiple; gets multiplied by the number of spline points in the pipeline and determines the ultimate size of actor pool. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SizeFactor = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AOreBuildingBase* Offtaker;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bInfected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSwitchedOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 2000;
};
