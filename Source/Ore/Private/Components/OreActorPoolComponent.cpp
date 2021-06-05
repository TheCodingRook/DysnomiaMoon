// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "Components/OreActorPoolComponent.h"
#include "LevelElements/MovingOreLump.h"
#include "Interfaces/OreActorPoolInterface.h"

// Sets default values for this component's properties
UOreActorPoolComponent::UOreActorPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxSize = 1000;
}

// Called every frame
void UOreActorPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UOreActorPoolComponent::RemoveFromPool()
{
	if(Members.Num() > 0)
	{
		AActor* PoppedActor = Members.Pop();
		if (PoppedActor)
		{
			PoppedActor->SetActorHiddenInGame(false);
			return PoppedActor;
		}
		return nullptr;
	}
	
	if(Size < MaxSize)
	{
		// Array is empty but we are still allowed to spawn more elements
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = GetOwner();
		AActor* NewActor = GetWorld()->SpawnActor<AActor>(ActorClass, FTransform::Identity,ActorSpawnParameters);
		if(NewActor)
		{
			++Size;
			return NewActor;
		}
		
		UE_LOG(LogTemp, Error, TEXT("%s: Error trying to spawn new OreLump actor!"), *GetOwner()->GetName());
		return nullptr;
	}
		
	UE_LOG(LogTemp, Error, TEXT("%s: Reached the maximum size in the OreActorPool and couldn't spawn more!"), *GetOwner()->GetName());
	return nullptr;
}

void UOreActorPoolComponent::ReturnToPool(AActor* ActorToReturn)
{
	if(ActorToReturn)
	{
		ActorToReturn->SetActorHiddenInGame(true);
		ActorToReturn->SetActorLocation(FVector::ZeroVector);
		if(ActorToReturn->Implements<UOreActorPoolInterface>())
		{
			IOreActorPoolInterface::Execute_ResetValues(ActorToReturn);
		}
		
		Members.Push(ActorToReturn);		
	}
	else
	{
		UE_LOG(LogTemp, Error,TEXT("Attempted to return null actor back to: %s"), *GetOwner()->GetName());
	}
	

}

void UOreActorPoolComponent::InitActorPool(TSubclassOf<AActor> InActorClass, int32 InPoolSize)
{
	if(InActorClass)
	{
		ActorClass = InActorClass;
		for (int i = 0; i <= FMath::Min(MaxSize,InPoolSize) - 1; i++)
		{
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Owner = GetOwner();
			ReturnToPool(GetWorld()->SpawnActor<AActor>(InActorClass, FTransform::Identity, ActorSpawnParameters));
			++Size;
		}

		if(InPoolSize > MaxSize)
		{
			UE_LOG(LogTemp, Error, TEXT("The desired poolsize for [%s] exceeded the maximum allowed!"), *GetOwner()->GetName());
		}
	}
}

int UOreActorPoolComponent::GetSize() const
{
	return Size;	
}

// Called when the game starts
void UOreActorPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



