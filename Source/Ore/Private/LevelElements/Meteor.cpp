// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/Meteor.h"
#include "Components/SphereComponent.h"

// Sets default values
AMeteor::AMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	//SetRootComponent(DefaultRoot);

	MeteorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeteorMesh"));
	SetRootComponent(MeteorMesh);
	
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	CollisionVolume->SetupAttachment(MeteorMesh);

}

// Called when the game starts or when spawned
void AMeteor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeteor::SetupValues_Implementation()
{
	MeteorMesh->SetSimulatePhysics(true);
	MeteorMesh->SetLinearDamping(.75f);
	MeteorMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	MeteorMesh->SetGenerateOverlapEvents(true);
	CollisionVolume->SetGenerateOverlapEvents(true);
	CollisionVolume->SetLinearDamping(.75f);
	SetActorHiddenInGame(false);
}

void AMeteor::ResetValues_Implementation()
{
	MeteorMesh->SetSimulatePhysics(false);
	MeteorMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	MeteorMesh->SetGenerateOverlapEvents(false);
	CollisionVolume->SetGenerateOverlapEvents(false);
	SetActorHiddenInGame(true);
}

