// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "OreProjectile.generated.h"

// Forward declarations
class UProjectileMovementComponent;

UCLASS()
class ORE_API AOreProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOreProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnProjectileImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Destroy this projectile after a while
	UFUNCTION()
	void EndProjectileLife();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected: // Properties

	/** The main root component for the projectile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* DefaultRoot;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* BulletCollision;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BulletMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	// How long before this projectile is automatically destroyed
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LifeSpan;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageDealt;

};
