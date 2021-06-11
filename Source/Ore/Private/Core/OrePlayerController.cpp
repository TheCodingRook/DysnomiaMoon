
// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/OrePlayerController.h"

#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/OreBombingComponent.h"
#include "Pawns/OreCharacter.h"
#include "Pawns/OreCharacter3P.h"
#include "Pawns/OreFighterJet.h"
#include "Engine/World.h"
#include "Components/InteractionComponentBase.h"
#include "Core/OreGameplayStatics.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/OreHUD.h"

AOrePlayerController::AOrePlayerController()
{
	//bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AOrePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


}

void AOrePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AOrePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AOrePlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AOrePlayerController::Fire);
	InputComponent->BindAction("DropBomb", IE_Pressed, this, &AOrePlayerController::DropBomb);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AOrePlayerController::Interact);
	InputComponent->BindAction("ExitSpacecraft", IE_Pressed, this, &AOrePlayerController::ExitSpacecraft);

	InputComponent->BindAxis("MoveForward", this, &AOrePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AOrePlayerController::MoveRight);
	InputComponent->BindAxis("MoveUp", this, &AOrePlayerController::MoveUp);

	InputComponent->BindAxis("TurnRate", this, &AOrePlayerController::TurnRate);
	InputComponent->BindAxis("LookUpRate", this, &AOrePlayerController::LookUpRate);
	
	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AOrePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AOrePlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AOrePlayerController::OnResetVR);

	InputComponent->BindAction("Pause", IE_Pressed, this, &AOrePlayerController::PauseOreGame);
}

void AOrePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(InPawn->IsA(AOreCharacter::StaticClass()))
	{
		AOreCharacter* OreCharacter = Cast<AOreCharacter>(InPawn);
		AstroMiner = OreCharacter;
		PlayerMovementMode = EOreMovementMode::OnFoot;
		AstroMiner->SetupPlayerControllerRef(this);
		//FighterJet->SetupPlayerControllerRef(nullptr);

		bShowMouseCursor = true;
		DefaultMouseCursor = EMouseCursor::Crosshairs;
		FighterJet = nullptr;
	}
	else if(InPawn->IsA(AOreCharacter3P::StaticClass()))
	{
		AOreCharacter3P* OreCharacter3P = Cast<AOreCharacter3P>(InPawn);
		AstroMiner = OreCharacter3P;
		PlayerMovementMode = EOreMovementMode::OnFoot;
		AstroMiner->SetupPlayerControllerRef(this);
		//FighterJet = nullptr;
	}
	else if(AOreFighterJet* OreFighterJet = Cast<AOreFighterJet>(InPawn))
	{
		FighterJet = OreFighterJet;
		PlayerMovementMode = EOreMovementMode::Piloting;
		FighterJet->SetupPlayerControllerRef(this);
		UOreGameplayStatics::GetOreGameMode(this)->MainHUD->ShowSpacecraftHealthBar();
	}
}

void AOrePlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AOrePlayerController::MoveToMouseCursor()
{
	if(AOreCharacter* AstroMinerTopDown = Cast<AOreCharacter>(AstroMiner))
	{
		AstroMinerTopDown->MoveToMouseCursor();
	}
}

void AOrePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if(AOreCharacter* AstroMinerTopDown = Cast<AOreCharacter>(AstroMiner))
	{
		AstroMinerTopDown->MoveToTouchLocation(FingerIndex, Location);
	}
}

void AOrePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if(AOreCharacter* AstroMinerTopDown = Cast<AOreCharacter>(AstroMiner))
	{
		AstroMinerTopDown->SetNewMoveDestination(DestLocation);
	}
}

void AOrePlayerController::OnSetDestinationPressed()
{
	if(AOreCharacter* AstroMinerTopDown = Cast<AOreCharacter>(AstroMiner))
	{
		AstroMinerTopDown->OnSetDestinationPressed();	
	}
}

void AOrePlayerController::OnSetDestinationReleased()
{
	if(AOreCharacter* AstroMinerTopDown = Cast<AOreCharacter>(AstroMiner))
	{
		AstroMinerTopDown->OnSetDestinationReleased();	
	}
}

void AOrePlayerController::Fire()
{
	switch (PlayerMovementMode)
	{
	case (EOreMovementMode::OnFoot) :
		if(AstroMiner)
		{
			if(AstroMiner->GetFiringComponent())
			{
				AstroMiner->GetFiringComponent()->FireWeapon();
			}
		}
		break;

	case (EOreMovementMode::Piloting) :
		if(FighterJet)
		{
			if(FighterJet->GetFiringComponent())
            	{
            		FighterJet->GetFiringComponent()->FireWeapon();
            	}
		}
		break;
	}

}

void AOrePlayerController::DropBomb()
{
	if(FighterJet && PlayerMovementMode == EOreMovementMode::Piloting)
	{
		FighterJet->GetBombingComponent()->FireWeapon();
	}
}

void AOrePlayerController::Interact()
{
	if (UInteractionComponentBase* InteractionToExecute = UOreGameplayStatics::GetOreGameInstance(this)->GetLatestInteraction())
	{
		InteractionToExecute->ExecuteInteraction(this);
	}
}

void AOrePlayerController::MoveForward(float Value)
{
//	float HeldTime = 0.f;
	if (Value != 0)
	{
		if(PlayerMovementMode == EOreMovementMode::Piloting && FighterJet != nullptr)
		{
			FighterJet->AddMovementInput(FVector(Value, 0.f, 0.f), 2.f, false);
			// Drop the Z-axis from the velocity vector
			GetPawn()->SetActorRotation(FVector(/*FighterJet*/GetPawn()->GetMovementComponent()->Velocity.X, /*FighterJet*/GetPawn()->GetMovementComponent()->Velocity.Y, 0.f).Rotation());
			return;
		}
		if(PlayerMovementMode == EOreMovementMode::OnFoot && AstroMiner->IsA(AOreCharacter3P::StaticClass()))
		{
			const FRotator Rotation = GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AstroMiner->AddMovementInput(Direction, Value);
		
		}
	}
}

void AOrePlayerController::MoveRight(float Value)
{
//	float HeldTime = 0.f;
	if (Value != 0)
	{
		if(PlayerMovementMode == EOreMovementMode::Piloting && FighterJet != nullptr)
		{
			/*FighterJet*/GetPawn()->AddMovementInput(FVector(0.f, Value, 0.f), 2.f, false);
			// Drop the Z-axis from the velocity vector
			/*FighterJet*/GetPawn()->SetActorRotation(FVector(/*FighterJet*/GetPawn()->GetMovementComponent()->Velocity.X, /*FighterJet*/GetPawn()->GetMovementComponent()->Velocity.Y, 0.f).Rotation());
			return;
		}

		if(PlayerMovementMode == EOreMovementMode::OnFoot && AstroMiner->IsA(AOreCharacter3P::StaticClass()))
		{
			// find out which way is right
			const FRotator Rotation = GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
	
			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AstroMiner->AddMovementInput(Direction, Value);
		}
	}

}

void AOrePlayerController::MoveUp(float Value)
{
	if (Value != 0)
	{
		if(PlayerMovementMode == EOreMovementMode::Piloting && FighterJet != nullptr)
		{
			/*FighterJet*/GetPawn()->AddMovementInput(FVector(0.f, 0.f, Value), 1.f, false);
		}		
	}
}

void AOrePlayerController::TurnRate(float Rate)
{
	if (Rate != 0)
	{
		if(PlayerMovementMode == EOreMovementMode::OnFoot && AstroMiner->IsA(AOreCharacter3P::StaticClass()))
		{
			// calculate delta for this frame from the rate information
			AddYawInput(Rate * 45.f * GetWorld()->GetDeltaSeconds());		
		}
		
	}
}

void AOrePlayerController::LookUpRate(float Rate)
{
	if (Rate != 0)
	{
		if (PlayerMovementMode == EOreMovementMode::OnFoot && AstroMiner->IsA(AOreCharacter3P::StaticClass()))
		{
			// calculate delta for this frame from the rate information
			AddPitchInput(Rate * 45.f * GetWorld()->GetDeltaSeconds());
		}		
	}
}

void AOrePlayerController::ExitSpacecraft()
{
	if (FighterJet)
	{
		// Ignore self
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(FighterJet);
		const FVector StartLocation = FighterJet->GetFighterJetMesh()->GetSocketTransform(TEXT("DisembarkLeft")).GetLocation();
		const FVector EndLocation = StartLocation + FVector(0.f, 0.f, -100.f);
		
		
		FHitResult OutHit;
		
		bool bLandingSpotDetected = UKismetSystemLibrary::SphereTraceSingle(
        this,
        StartLocation,
        EndLocation,
        50.f,
        ETraceTypeQuery::TraceTypeQuery2, // Should be for BlockAll?
        false,
        ActorsToIgnore,
        EDrawDebugTrace::None,
        OutHit,
        false);

		if (bLandingSpotDetected && AstroMiner != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Can disembark now..."));
			AstroMiner->SetActorHiddenInGame(false);
			if(AstroMiner->GetFiringComponent()->EquippedWeapon != nullptr)
			{
				TArray<AActor*> AttachedActors;
				AstroMiner->GetAttachedActors(AttachedActors);
				for(AActor* Actor : AttachedActors)
				{
					Actor->SetActorHiddenInGame(false);				
				}
			}	

		
			AstroMiner->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			AstroMiner->SetActorLocation(StartLocation);
			//AstroMiner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			AstroMiner->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
			Possess(AstroMiner);
			AstroMiner->GetMovementComponent()->ResetMoveState();
			UOreGameplayStatics::GetOreGameMode(this)->MainHUD->HideSpacecraftHealthBar();
		}
	}
	

}

void AOrePlayerController::PauseOreGame_Implementation()
{
	//native code here if needed
}

AOreCharacterBase* AOrePlayerController::GetAstroMiner() const
{
	return AstroMiner;
}

void AOrePlayerController::OnSpacecraftDestroyed()
{
	AstroMiner->SetActorHiddenInGame(false);
	if(AstroMiner->GetFiringComponent()->EquippedWeapon != nullptr)
	{
		TArray<AActor*> AttachedActors;
		AstroMiner->GetAttachedActors(AttachedActors);
		for(AActor* Actor : AttachedActors)
		{
			Actor->SetActorHiddenInGame(false);				
		}
	}	

		
	AstroMiner->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	AstroMiner->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	Possess(AstroMiner);
	AstroMiner->GetMovementComponent()->ResetMoveState();
	UOreGameplayStatics::GetOreGameMode(this)->MainHUD->HideSpacecraftHealthBar();
	UOreGameplayStatics::GetOreGameMode(this)->MainHUD->DisplayFigherJetDestroyedWarning();
	if(FighterJet)
	{
		// Get read of the guns of this spacecraft
		TArray<AActor*> AttachedWeapons;
		FighterJet->GetAttachedActors(AttachedWeapons);
		for (auto AttachedWeapon : AttachedWeapons)
		{
			AttachedWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			AttachedWeapon->Destroy();
		}
		
		AstroMiner->SetActorLocation(FighterJet->GetActorLocation());
		FighterJet->Destroy();
	}
	
}
