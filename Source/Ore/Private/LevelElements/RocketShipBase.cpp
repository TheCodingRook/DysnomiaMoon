// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/RocketShipBase.h"

// Sets default values
ARocketShipBase::ARocketShipBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bInLaunchPosition = true;

}

// Called when the game starts or when spawned
void ARocketShipBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARocketShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARocketShipBase::GetInfected_Implementation()
{
	bInfected = true;
}

void ARocketShipBase::OnInfectionCleared_Implementation()
{
	bInfected = false;
}

