// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/OreMineBase.h"



#include "Core/OreGameplayStatics.h"
#include "LevelElements/InfectionSpawnVolume.h"
#include "LevelElements/OreInfectionManagerBase.h"
#include "LevelElements/OrePipeline.h"
#include "UI/OreHUD.h"

// Sets default values
AOreMineBase::AOreMineBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AOreMineBase::IsInfected() const
{
	return bInfected;
}

void AOreMineBase::GetInfected_Implementation()
{
	SetInfectionState(true);

	// Start spawning the visual representation of the infection in the mine
	if(InfectionSpawner)
	{
		InfectionSpawner->StartInfection();
	}
	
	// Infect the pipelines
	for(auto Pipeline : Pipelines)
	{
		if (Pipeline)
		{
			if(Pipeline->Implements<UOreInfectionInterface>())
			{
				IOreInfectionInterface::Execute_GetInfected(Pipeline);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Attempted to use GetInfected of IOreInfectionInterface but %s does not implement it!"), *Pipeline->GetClass()->GetName());
			}			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Null pipeline reference detected for: %s"), *GetName());
		}
		
	}
}

void AOreMineBase::OnInfectionCleared_Implementation()
{
	SetInfectionState(false);
	UOreGameplayStatics::GetOreGameMode(this)->MainHUD->UpdateInfectionsCounter(-1);
	if(MyInfectionManager)
	{
		MyInfectionManager->OnMineInfectionCleared(MineName);
	}
	for(auto Pipeline : Pipelines)
	{
		if (Pipeline)
		{
			if(Pipeline->Implements<UOreInfectionInterface>())
			{
				IOreInfectionInterface::Execute_OnInfectionCleared(Pipeline);
			}
			else
			{
#if !UE_BUILD_SHIPPING
				UE_LOG(LogTemp, Error, TEXT("Attempted to use OnInfectionCleared of IOreInfectionInterface but %s does not implement it!"), *Pipeline->GetClass()->GetName());
#endif

			}			
		}
		else
		{
#if !UE_BUILD_SHIPPING
			UE_LOG(LogTemp, Warning, TEXT("Null pipeline reference detected for: %s"), *GetName());
#endif
		}
		
	}
}

void AOreMineBase::OnMineDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
}

// Called when the game starts or when spawned
void AOreMineBase::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AOreMineBase::OnMineDamaged);

	if(InfectionSpawner)
	{
		//Set the reference to us
		InfectionSpawner->SetMineReference(this);
	}
	
	
}

// Called every frame
void AOreMineBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOreMineBase::SetInfectionState(bool bInfectionState)
{
	bInfected = bInfectionState;
}

