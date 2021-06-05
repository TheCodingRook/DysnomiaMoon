// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/OreLumpBase.h"

// Sets default values
AOreLumpBase::AOreLumpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(DefaultSceneRoot);

}

// Called when the game starts or when spawned
void AOreLumpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOreLumpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* AOreLumpBase::GetMesh() const
{
	return Mesh;
}

void AOreLumpBase::GetInfected_Implementation()
{
	bInfected = true;
}

void AOreLumpBase::OnInfectionCleared_Implementation()
{
	bInfected = false;
}

bool AOreLumpBase::IsInfected() const
{
	return bInfected;
}

