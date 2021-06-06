// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "Components/LaunchInteraction.h"

ULaunchInteraction::ULaunchInteraction()
{
	InteractionText = FText::FromString("Emergency Launch").ToUpper();
}

void ULaunchInteraction::ExecuteInteraction(AOrePlayerController* Instigator)
{
	Super::ExecuteInteraction(Instigator);
	EmergengyLaunch();
}
