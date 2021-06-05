// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "Components/BoardSpacecraft.h"

#include "Components/OreFiringComponent.h"
#include "Components/WidgetComponent.h"
#include "Core/OreGameplayStatics.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapons/OreWeapon.h"

UBoardSpacecraft::UBoardSpacecraft()
{
	InteractionText = FText::FromString("Board spacecraft").ToUpper();
}

void UBoardSpacecraft::ExecuteInteraction(AOrePlayerController* Instigator)
{
	Super::ExecuteInteraction(Instigator);
	AOreCharacterBase* OreCharacter = Instigator->GetAstroMiner();
	
	if (Instigator->PlayerMovementMode != EOreMovementMode::Piloting)
	{
		if (OreCharacter)
		{
			OreCharacter->SetActorHiddenInGame(true);
			if(OreCharacter->GetFiringComponent()->EquippedWeapon != nullptr)
			{
				OreCharacter->GetFiringComponent()->EquippedWeapon->SetActorHiddenInGame(true);
				OreCharacter->GetMovementComponent()->StopMovementImmediately();
			}
			
			OreCharacter->GetCapsuleComponent()->SetCollisionProfileName(TEXT("OverlapAll"));
			OreCharacter->AttachToActor(GetOwner(),FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		
		Instigator->Possess(Cast<APawn>(GetOwner()));
		WidgetComponent->SetVisibility(false);
	}
}

void UBoardSpacecraft::StopInteraction(AOrePlayerController* Instigator)
{
	Super::StopInteraction(Instigator);
}
