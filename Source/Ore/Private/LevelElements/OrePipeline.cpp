// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/OrePipeline.h"
#include "Components/SplineComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/OreActorPoolComponent.h"
#include "Components/SwitchInteraction.h"
#include "LevelElements/MovingOreLump.h"
#include "Interfaces/OreActorPoolInterface.h"
#include "LevelElements/OreBuildingBase.h"

// Sets default values
AOrePipeline::AOrePipeline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UBillboardComponent>("Location Sprite");
	SetRootComponent(Sprite);
	
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);

	OreActorPool = CreateDefaultSubobject<UOreActorPoolComponent>(TEXT("OreActorPoolComponent"));

	// Set up the interaction component
	SwitchInteractionComponent = CreateDefaultSubobject<USwitchInteraction>(TEXT("SwitchInteractionComponent"));
	
}

// Called every frame
void AOrePipeline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOrePipeline::GetInfected_Implementation()
{
	bInfected = true;
}

void AOrePipeline::OnInfectionCleared_Implementation()
{
	bInfected = false;

	/** Help the player here: 'disinfect' the contents of the pipeline, in case we have fought the infection off
	 * at the mine site, but have NOT turned the valve off (meaning infected ore is still flowing towards offtaker!
	 */

	for (auto MovingOreLump : MovingOreLumps)
	{
		MovingOreLump->bInfected = false;
	}
	
	if(Offtaker != nullptr && Offtaker->Implements<UOreInfectionInterface>())
	{
		IOreInfectionInterface::Execute_OnInfectionCleared(Offtaker);
	}	
}

bool AOrePipeline::IsInfected() const
{
	return bInfected;
}

bool AOrePipeline::IsSwitchedOn() const
{
	return bSwitchedOn;
}

void AOrePipeline::OnSwitchToggled_Implementation(bool InSwitchState)
{
	bSwitchedOn = InSwitchState;

	if(!bSwitchedOn)
	{
		// "Flush" the pipeline
		for (auto MovingOreLump : MovingOreLumps)
		{
			if(MovingOreLump->Implements<UOreActorPoolInterface>())
			{
				IOreActorPoolInterface::Execute_ResetValues(MovingOreLump);
			}
			OreActorPool->ReturnToPool(MovingOreLump);		
		}
		MovingOreLumps.Empty();
		ElapsedTime = 0.f;

		// If this also happens to be an 'infected' pipeline then also clear the infection
		if(bInfected)
		{
			OnInfectionCleared_Implementation();		
		}
	}
}

// Called when the game starts or when spawned
void AOrePipeline::BeginPlay()
{
	Super::BeginPlay();

	OreActorPool->InitActorPool(OreClass, SizeFactor * SplineComponent->GetNumberOfSplinePoints());
	OnTakeAnyDamage.AddDynamic(this, &AOrePipeline::OnPipelineDamaged);	
}

void AOrePipeline::OnPipelineDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
}

