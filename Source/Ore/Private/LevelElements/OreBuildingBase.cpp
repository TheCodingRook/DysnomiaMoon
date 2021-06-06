// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/OreBuildingBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/BillboardComponent.h"
#include "LevelElements/OreLumpBase.h"
#include "Components/SwitchInteraction.h"
#include "LevelElements/RocketShipBase.h"

// Sets default values
AOreBuildingBase::AOreBuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UBillboardComponent>("Location Sprite");
	SetRootComponent(Sprite);
	
	WidgetCapsule = CreateDefaultSubobject<UCapsuleComponent>("Widget Trigger");
	WidgetCapsule->SetupAttachment(Sprite);
	WidgetCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

	WidgetCapsuleReset = CreateDefaultSubobject<UCapsuleComponent>("Widget Reset Trigger");
	WidgetCapsuleReset->SetupAttachment(Sprite);
	WidgetCapsuleReset->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	BlockVolume = CreateDefaultSubobject<UCapsuleComponent>("Capsule Block Volume");
	BlockVolume->SetupAttachment(Sprite);

	// Set up the interaction component
	SwitchInteractionComponent = CreateDefaultSubobject<USwitchInteraction>(TEXT("SwitchInteractionComponent"));
	
}

void AOreBuildingBase::SetPower(bool InPowerState)
{
	bPoweredOn = InPowerState;
	if(LocationType == ELocationType::PowerPlant)
	{
		for (AOreBuildingBase* Building : ConnectedInfrastructure)
		{
			Building->bPoweredOn = InPowerState;
		}
	}
}

void AOreBuildingBase::OnSwitchToggled_Implementation(bool InSwitchState)
{
	// Only allow flicking the switch if this building is already connected to power plant
	if(bPoweredOn)
	{
		bSwitchedOn = InSwitchState;
	}
}

void AOreBuildingBase::AcceptResourceFromPipeline(EOreType InResourceType, float InQuantity)
{
	for (int i = 0; i <= Resources.Num()-1; i++)
	{
		if(Resources[i].ResourceType == InResourceType)
		{
			Resources[i].Quantity += InQuantity;
		}
	}
}

void AOreBuildingBase::GetInfected_Implementation()
{
	bInfected = true;
}

void AOreBuildingBase::OnInfectionCleared_Implementation()
{
	bInfected = false;
}

bool AOreBuildingBase::CheckResources()
{
	for(auto Resource : Resources)
	{
		if(Resource.Quantity <= 0)
		{
			return false;
		}
	}
	return true;
}

ELocationType AOreBuildingBase::GetLocationType() const
{
	return LocationType;
}

void AOreBuildingBase::OnBuildingDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
}

// Called when the game starts or when spawned
void AOreBuildingBase::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AOreBuildingBase::OnBuildingDamaged);
	
	// For power plants only: set the power status to connected infrastructure
	if(LocationType == ELocationType::PowerPlant)
	{
		for(AOreBuildingBase* Building : ConnectedInfrastructure)
		{
			Building->bPoweredOn = bPoweredOn;
		}
	}
	
}

// Called every frame
void AOreBuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(LocationType == ELocationType::GoldWarehouse && RocketShip != nullptr)
	{
		if(RocketShip->bInLaunchPosition)
		{
			for (int i = 0; i <= Resources.Num()-1; i++)
			{
				if (Resources[i].ResourceType == EOreType::Gold)
				{
					// Deal with gold
					float MaxGoldRocketCanTake = FMath::Min(RocketShip->MaxGoldCapacity - RocketShip->LoadedGold, Resources[i].SpendPerSecond * DeltaTime);
					float MaxGoldWarehouseCanGive = FMath::Min(Resources[i].Quantity, Resources[i].SpendPerSecond * DeltaTime);
					RocketShip->LoadedGold += FMath::Min(MaxGoldRocketCanTake, MaxGoldWarehouseCanGive);
					if (bInfected)
					{
						// If this building (i.e. GoldWarehouse) is infected, then load up infected amount as well!
						RocketShip->LoadedParasite += FMath::Min(Resources[i].Quantity, Resources[i].SpendPerSecond * DeltaTime);
					}
					Resources[i].Quantity -= FMath::Min(MaxGoldRocketCanTake, MaxGoldWarehouseCanGive);
				
				}
				else if(Resources[i].ResourceType == EOreType::Fuel && !bInfected) // If this building (i.e. GoldWarehouse) is infected, stop fueling of the RocketShip!
				{
					// Deal with fuel
					float MaxFuelRocketCanTake = FMath::Min(RocketShip->MinFuelRequired - RocketShip->LoadedFuel, Resources[i].SpendPerSecond * DeltaTime);
					float MaxFuelWarehouseCanGive = FMath::Min(Resources[i].Quantity, Resources[i].SpendPerSecond * DeltaTime);
					RocketShip->LoadedFuel += FMath::Min(MaxFuelRocketCanTake, MaxFuelWarehouseCanGive);
					Resources[i].Quantity -= FMath::Min(MaxFuelRocketCanTake, MaxFuelWarehouseCanGive);				
				}

			}			
		}

	}
	else
	{
		for (int i = 0; i <= Resources.Num()-1; i++)
		{
			Resources[i].Quantity = FMath::Max(0.f, Resources[i].Quantity - Resources[i].SpendPerSecond * DeltaTime);
		}		
		
	}
}

bool AOreBuildingBase::IsInfected() const
{
	return bInfected;
}

bool AOreBuildingBase::IsPoweredOn() const
{
	return bPoweredOn;
}

bool AOreBuildingBase::IsSwitchedOn() const
{
	return bSwitchedOn;
}

void AOreBuildingBase::OnBuildingInfected_Implementation()
{
	if(LocationType == ELocationType::PowerPlant)
	{
		SetPower(false);
	}
}

