// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/GoldWarehouse.h"
#include "LevelElements/OreBuildingBase.h"
#include "LevelElements/OreLumpBase.h"
#include "LevelElements/RocketShipBase.h"

void AGoldWarehouse::Tick(float DeltaSeconds)
{
	AActor::Tick(DeltaSeconds);

	for (int i = 0; i <= Resources.Num()-1; i++)
	{
		if (Resources[i].ResourceType == EOreType::Gold)
		{UE_LOG(LogTemp, Warning, TEXT("sajkfksdjfaskjf"));
			Resources[i].Quantity = FMath::Max(0.f, Resources[i].Quantity - LoadRocketShip(Resources[i].SpendPerSecond * DeltaSeconds));
		}
		else
		{
			Resources[i].Quantity = FMath::Max(0.f, Resources[i].Quantity - Resources[i].SpendPerSecond * DeltaSeconds);			
		}
	}
}

float AGoldWarehouse::LoadRocketShip(float InQuantity)
{
	if(RocketShip)
	{
		RocketShip->LoadedGold += FMath::Min(InQuantity, RocketShip->MaxGoldCapacity - RocketShip->LoadedGold);
		return FMath::Min(InQuantity, RocketShip->MaxGoldCapacity - RocketShip->LoadedGold);
	}
	else
	{
		return 0.f;
	}
}
