// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "InteractionComponentBase.generated.h"

// Forward declarations
class AOrePlayerController;
class UWidgetComponent;
class UInteractionWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ORE_API UInteractionComponentBase : public UCapsuleComponent
{
	GENERATED_BODY()

	public:	
	// Sets default values for this component's properties
	UInteractionComponentBase();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ExecuteInteraction(AOrePlayerController* Instigator);
	virtual void StopInteraction(AOrePlayerController* Instigator);
	
	UFUNCTION(BlueprintCallable, Category = "Overlaps")
    virtual void OnInteractionVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Overlaps")
    virtual void OnInteractionVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintPure, Category = "Widget")
    FText GetInteractionText() const { return InteractionText; }

	protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// What is the prompt for this interaction? - If not set in code, remember to set in Blueprint
	UPROPERTY(EditAnywhere, Category = "Widget")
	FText InteractionText;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	class UWidgetComponent* WidgetComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UInteractionWidget> MyWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FVector2D WidgetDrawSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FVector WidgetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FRotator WidgetRotation;
};
