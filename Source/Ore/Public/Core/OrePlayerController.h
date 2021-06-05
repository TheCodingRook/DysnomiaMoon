// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OrePlayerController.generated.h"

/** Custom Enum type to describe the gameplay mode the player is in: on foot or piloting a spacecraft */
UENUM(BlueprintType)
enum class EOreMovementMode : uint8
{
	OnFoot UMETA(DisplayName = "On Foot"),
	Piloting UMETA(DisplayName = "Piloting")
};

// Forward declarations
class AOreCharacterBase;
class AOreFighterJet;

UCLASS()
class AOrePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AOrePlayerController();

	/* Get the reference to our bipedal character */
	AOreCharacterBase* GetAstroMiner() const;

	UFUNCTION(BlueprintCallable)
	void OnSpacecraftDestroyed();

	/* Pause the game */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void PauseOreGame();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	//virtual  void OnUnPossess() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);
	
	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	/* Fire a weapon if we are holding one (works for both player character and fighter spacecraft */
	void Fire();

	/* Drop a bomb (only works when piloting the spacecraft */
	void DropBomb();
	
	/* Interact with an interactable actor / element in the world */
	void Interact();

	/* Move forward when piloting a spacecraft */
	void MoveForward(float Value);

	/* Move right when piloting a spacecraft */
	void MoveRight(float Value);

	/* Move up when piloting a spacecraft */
	void MoveUp(float Value);

	/* Exit a spacecraft */
	void ExitSpacecraft();

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
	EOreMovementMode PlayerMovementMode;

protected:
	/* A reference to our character when we possess one */
	AOreCharacterBase* AstroMiner;
	
	/* A reference to our spacecraft when we possess one */
	AOreFighterJet* FighterJet;

	/* A reference to the pause menu widget class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;
};


