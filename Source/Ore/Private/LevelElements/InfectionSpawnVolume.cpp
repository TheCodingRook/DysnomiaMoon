// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "LevelElements/InfectionSpawnVolume.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "Interfaces/OreInfectionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"

AInfectionSpawnVolume::AInfectionSpawnVolume()
{
	Sprite = CreateDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));
	SetRootComponent(Sprite);
	
	VolumeShape = CreateDefaultSubobject<USphereComponent>(TEXT("InfectionSpawner"));
	VolumeShape->SetupAttachment(Sprite);
	Cast<USphereComponent>(VolumeShape)->SetSphereRadius(200.f);
}

void AInfectionSpawnVolume::StartInfection()
{
	// Reset this flag
	bFirstSpawn = true;
	
	// Start a spawning loop;
	GetWorldTimerManager().SetTimer(InfectionSpawnTimer, this, &AInfectionSpawnVolume::SpawnBlob, bFixedFrequency? SpawnFrequency : FMath::RandRange(MinSpawnDelay, MaxSpawnDelay), true);
	
	}

void AInfectionSpawnVolume::SpawnBlob()
{
	if(bFirstSpawn || SpawnCount > 0)
	{
		FVector RandomVector = FMath::VRand();
		RandomVector.Z = FMath::Abs(RandomVector.Z);
		FVector RandomLocation = RandomVector * Cast<USphereComponent>(VolumeShape)->GetUnscaledSphereRadius();

		// Ignore self
		TArray<AActor*> ActorsToIgnore;
		//ActorsToIgnore.Add(FighterJet);
		const FVector StartLocation = VolumeShape->GetComponentLocation() + RandomVector * Cast<USphereComponent>(VolumeShape)->GetUnscaledSphereRadius();
		const FVector EndLocation = StartLocation + FVector(0.f, 0.f, -0.f);
		
		
		FHitResult OutHit;
		bool ObstacleFound = true;
		for (int i = 0; i < 100; i++)
		{
			ObstacleFound = UKismetSystemLibrary::SphereTraceSingle(
            this,
            StartLocation,
            EndLocation,
            60.f,
            ETraceTypeQuery::TraceTypeQuery2, // Should be for BlockAll?
            false,
            ActorsToIgnore,
            EDrawDebugTrace::None,
            OutHit,
            false);
			
		
	
			if (!ObstacleFound)
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = this;
				// Spawn a blob here
				const FTransform SpawnTransform = FTransform(FRotator(0.f, 0.f, 0.f),StartLocation,  FVector(1.f, 1.f, 1.f));
				AActor* NewInfectionBlob = GetWorld()->SpawnActor<AActor>(SpawnActorClass, SpawnTransform, SpawnParameters);
				if (NewInfectionBlob)
				{
					++SpawnCount;
					bFirstSpawn = false;
					return;
				}
			}
		}
	}
	// We have cleared the infection
	else
	{
		GetWorldTimerManager().ClearTimer(InfectionSpawnTimer);
		//InfectionSpawnTimer.Invalidate();
		UE_LOG(LogTemp, Warning, TEXT("[%s]: Infection cleared!"), *GetName());

		if(MyMine && MyMine->Implements<UOreInfectionInterface>())
		{
			IOreInfectionInterface::Execute_OnInfectionCleared(MyMine);			
		}
	}

}

void AInfectionSpawnVolume::SetMineReference(AOreMineBase* InMineReference)
{
	MyMine = InMineReference;

}
