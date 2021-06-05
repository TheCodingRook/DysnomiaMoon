// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "Pawns/OreCharacterBase.h"
#include "Components/OreFiringComponent.h"

// Sets default values
AOreCharacterBase::AOreCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the main body mesh
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	// Create the Firing component
	FiringComponent = CreateDefaultSubobject<UOreFiringComponent>(TEXT("FiringComponent"));

}

// Called when the game starts or when spawned
void AOreCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOreCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOreCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UOreFiringComponent* AOreCharacterBase::GetFiringComponent() const
{
	return FiringComponent;
}

AOrePlayerController* AOreCharacterBase::GetOrePlayerController() const
{
	return OrePlayerController;
}

void AOreCharacterBase::SetupPlayerControllerRef(AOrePlayerController* InPlayerController)
{
	OrePlayerController = InPlayerController;
}

void AOreCharacterBase::HideCharacter()
{
	BodyMesh->SetVisibility(false, true);
}