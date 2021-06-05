// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OreCharacterBase.generated.h"

// Forward declarations
class UOreFiringComponent;
class AOrePlayerController;

UCLASS()
class ORE_API AOreCharacterBase : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AOreCharacterBase(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	/* Returns the Firing component */
	UOreFiringComponent* GetFiringComponent() const;

	/* Sets a reference to our PlayerController */
	void SetupPlayerControllerRef(AOrePlayerController* InPlayerController);
	
	/* Returns the reference to OrePlayerController */
	AOrePlayerController* GetOrePlayerController() const;	

	/* Called to hide character if necessary, for example when boarding a space craft */
	UFUNCTION(BlueprintCallable)
    void HideCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite)
	bool bArmed;

protected:

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** The main static mesh associated with this Character. */
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	UOreFiringComponent* FiringComponent;

	AOrePlayerController* OrePlayerController;

};
