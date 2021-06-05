// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OreFiringComponent.generated.h"

class AOreWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ORE_API UOreFiringComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOreFiringComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AOreWeapon* GetEquippedWeapon() const;

	virtual void FireWeapon();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public: // Properties

	// The weapon character is currently holding
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AOreWeapon* EquippedWeapon;

		
};
