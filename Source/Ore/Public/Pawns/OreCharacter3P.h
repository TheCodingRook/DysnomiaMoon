// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Pawns/OreCharacterBase.h"
#include "OreCharacter3P.generated.h"

UCLASS(config=Game)
class ORE_API AOreCharacter3P : public AOreCharacterBase
{
	GENERATED_BODY()

public:
	AOreCharacter3P(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExtendArmsLegsAtJump(float ArmRollDegrees, float LegRollDegrees);

	void OreCharacter3PJump();
	
	protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	//void MoveForward(float Value);

	/** Called for side to side input */
	//void MoveRight(float Value);

	/** 
	* Called via input to turn at a given rate. 
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate. 
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// How fast the character animates their arms when moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArmSpeed;
	
	// How fast the character animates their legs when moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LegSpeed;
	
	/** ~Scene components for the joints of the 4 limbs */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Joint_RightArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Joint_LeftArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Joint_RightLeg;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Joint_LeftLeg;
	
};

