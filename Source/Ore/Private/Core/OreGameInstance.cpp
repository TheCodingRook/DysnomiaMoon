// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "Core/OreGameInstance.h"

UInteractionComponentBase* UOreGameInstance::GetLatestInteraction()
{
	return LatestInteraction;
}

void UOreGameInstance::PushNewInteraction(UInteractionComponentBase* NewInteraction)
{
	LatestInteraction = NewInteraction;
}

void UOreGameInstance::PopInteraction()
{
	LatestInteraction = nullptr;
}
