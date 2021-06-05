// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/OreCharacterBase.h"
#include "Core/OrePlayerController.h"
#include "OreCharacter.generated.h"

class UOreFiringComponent;

UCLASS(config=Game)
class AOreCharacter : public AOreCharacterBase
{
	GENERATED_BODY()

public:
	AOreCharacter(const FObjectInitializer& ObjectInitializer);

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);
	
	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

private:

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

public:
	/** True if the controlled character should navigate to the mouse cursor. */
	bool bMoveToMouseCursor;
};

