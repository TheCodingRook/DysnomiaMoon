// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OreActorPoolComponent.generated.h"

//Forward declarations
//class AMovingOreLump;

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class ORE_API UOreActorPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOreActorPoolComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
    AActor* RemoveFromPool();

	UFUNCTION(BlueprintCallable)
	void ReturnToPool(AActor* ActorToReturn);

	UFUNCTION(BlueprintCallable, Category = "ActorPool")
	void InitActorPool(TSubclassOf<AActor> InActorClass, int32 InPoolSize);

	UFUNCTION(BlueprintPure)
	int GetSize() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

	TSubclassOf<AActor> ActorClass;
	
	UPROPERTY(BlueprintReadOnly);
	int Size;
	
	UPROPERTY(BlueprintReadWrite);
	int32 MaxSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AActor*> Members;

};

