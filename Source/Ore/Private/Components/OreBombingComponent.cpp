// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "Components/OreBombingComponent.h"
#include "Pawns/OreFighterJet.h"

void UOreBombingComponent::FireWeapon()
{
	if(AOreFighterJet* MyOwner = Cast<AOreFighterJet>(GetOwner()))
	{
		MyOwner->DropBomb_BP();
	}

	else
	{
		Super::FireWeapon();
	}
}
