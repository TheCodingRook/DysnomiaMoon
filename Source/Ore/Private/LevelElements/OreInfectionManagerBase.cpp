// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/OreInfectionManagerBase.h"
#include "LevelElements/OreMineBase.h"
#include "Interfaces/OreInfectionInterface.h"

// Sets default values
AOreInfectionManagerBase::AOreInfectionManagerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOreInfectionManagerBase::BeginPlay()
{
	Super::BeginPlay();
/*
	if(OreMines[1])
	{ // infect first one for now
		IOreInfectionInterface::Execute_GetInfected(OreMines[1]);
	}
	*/
}

// Called every frame
void AOreInfectionManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

