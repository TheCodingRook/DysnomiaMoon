// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OreFighterJet.generated.h"

// Forward declarations
class UBoxComponent;
class UCameraComponent;
class USpringArmComponent;
class AOrePlayerController;
class UBoardSpacecraft;
class UOreFiringComponent;
class UOreBombingComponent;

/**
* Custom enumeration type to explain who caused damage to the spacecraaft/fighter jet
*/
UENUM(BlueprintType)
enum class EFighterJetDamageType : uint8
{
	Meteor UMETA(DisplayName = "Meteor"),
    SAM UMETA(DisplayName = "MissileDefenseInstallation"),
};

UCLASS()
class ORE_API AOreFighterJet : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOreFighterJet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Mesh")
	UStaticMeshComponent* GetFighterJetMesh() const;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Sets a reference to our PlayerController */
	void SetupPlayerControllerRef(AOrePlayerController* InPlayerController);

	UFUNCTION(BlueprintCallable)
	void GetPossessedByPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnSpacecraftDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser );

	UFUNCTION(BlueprintCallable)
	UOreFiringComponent* GetFiringComponent() const;

	UFUNCTION(BlueprintCallable)
    UOreBombingComponent* GetBombingComponent() const;

	UFUNCTION(BlueprintImplementableEvent)
	void DropBomb_BP();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// properties

	UPROPERTY(EditDefaultsOnly)
	UBoardSpacecraft* BoardSpacecraft;
	
	// Basic collision volume
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* MeshCollision;
	
	/** The main static mesh for the weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* FighterJetMesh;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the fighter jet pawn */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	AOrePlayerController* OrePlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 500;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	UOreFiringComponent* FiringComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	UOreBombingComponent* BombingComponent;
};
