// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectiles/OreProjectile.h"

#include "OreWeapon.generated.h"

// Forward declarations
class AOreProjectile;

UCLASS()
class ORE_API AOreWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOreWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Get the mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	UStaticMeshComponent* GetWeaponMesh() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AOreProjectile> BulletClass;

	/** Sound to play each time we jump */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
	class USoundBase* FireSound;
	
protected: // for properties

	/** The main root component for the weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* DefaultRoot;
	
	/** The main static mesh for the weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* WeaponMesh;

	
	
};
