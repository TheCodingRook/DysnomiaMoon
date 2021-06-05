// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pawns/OreCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AOreCharacter::AOreCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	
	
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/ProjectOre/Player/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AOreCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	if(OrePlayerController != nullptr && OrePlayerController->PlayerMovementMode == EOreMovementMode::OnFoot)
	{
		if (CursorToWorld != nullptr)
		{
			if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
			{
				if (UWorld* World = GetWorld())
				{
					FHitResult HitResult;
					FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
					FVector StartLocation = CameraComponent->GetComponentLocation();
					FVector EndLocation = CameraComponent->GetComponentRotation().Vector() * 2000.0f;
					Params.AddIgnoredActor(this);
					World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
					FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
					CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
				}
			}
			else if (APlayerController* PC = Cast<APlayerController>(GetController()))
			{
				FHitResult TraceHitResult;
				PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
				FVector CursorFV = TraceHitResult.ImpactNormal;
				FRotator CursorR = CursorFV.Rotation();
				CursorToWorld->SetWorldLocation(TraceHitResult.Location);
				CursorToWorld->SetWorldRotation(CursorR);
			}

			
			
			// keep updating the destination every tick while desired
			if (bMoveToMouseCursor && OrePlayerController->PlayerMovementMode == EOreMovementMode::OnFoot)
			{
				MoveToMouseCursor();
			}		
		
		}	
	}
	
}

void AOreCharacter::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		
			if (GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(OrePlayerController, GetCursorToWorld()->GetComponentLocation());
			}
		
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		OrePlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AOreCharacter::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	OrePlayerController->GetHitResultAtScreenPosition(ScreenSpaceLocation, OrePlayerController->CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AOreCharacter::SetNewMoveDestination(const FVector DestLocation)
{
	
	
	
		float const Distance = FVector::Dist(DestLocation,GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(OrePlayerController, DestLocation);
		}
	
}

void AOreCharacter::OnSetDestinationPressed()
{
	if(OrePlayerController->PlayerMovementMode == EOreMovementMode::OnFoot)
	{
		// set flag to keep updating destination until released
		bMoveToMouseCursor = true;		
	}

}

void AOreCharacter::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}