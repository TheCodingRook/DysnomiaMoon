// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/MovingOreLump.h"

void AMovingOreLump::ResetValues_Implementation()
{
	CurrentSplineIndex = 0;
	OriginLocation = FVector::ZeroVector;
	TargetLocation = FVector::ZeroVector;
	bInfected = false;
}
