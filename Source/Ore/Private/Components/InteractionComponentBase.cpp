// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponentBase.h"
#include "Components/WidgetComponent.h"
#include "UI/InteractionWidget.h"
#include "Core/OreGameplayStatics.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInteractionComponentBase::UInteractionComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InteractionText = FText::FromString("Interact with").ToUpper();

	CapsuleHalfHeight = 200.f;
	CapsuleRadius = 50.f;

	WidgetDrawSize = FVector2D(100,100);
	WidgetLocation =FVector(0,0,100.f);
	WidgetRotation = FRotator(0.f, 180.f, 0.f);

	// Change the default response to all channels to Overlap
	SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called every frame
void UInteractionComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponentBase::ExecuteInteraction(AOrePlayerController* Instigator)
{
	// Potentially fire a delegate here

	//CODINGROOK_TODO: Some children though may need customization around the widget!
	WidgetComponent->SetVisibility(false);
	UOreGameplayStatics::GetOreGameMode(this)->HidePrompt();
}

void UInteractionComponentBase::StopInteraction(AOrePlayerController* Instigator)
{
	// Potentially fire a delegate here

	//CODINGROOK_TODO: Some children though may need customization around the widget!
	WidgetComponent->SetVisibility(true);
}


void UInteractionComponentBase::OnInteractionVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AOreCharacterBase* OverlappedActor = Cast<AOreCharacterBase>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player overlapped"))
		UOreGameplayStatics::GetOreGameInstance(GetOwner())->PushNewInteraction(this);

		// Set up a widget to indicate we can interact
		if (MyWidgetClass && nullptr == WidgetComponent)
		{
			WidgetComponent = NewObject<UWidgetComponent>(GetOwner(), UWidgetComponent::StaticClass(), TEXT("Widget"));
			WidgetComponent->RegisterComponent();
			WidgetComponent->SetWidgetClass(MyWidgetClass);
			WidgetComponent->SetDrawSize(WidgetDrawSize);
			//WidgetComponent->InitWidget();
			WidgetComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
			//UInteractionWidget* BoardInteractionWidget = CreateWidget<UInteractionWidget>(OverlappedActor->GetController(), MyWidgetClass, TEXT("Widget"));
			//BoardInteractionWidget->AddToViewport(0);
			WidgetComponent->SetRelativeLocation(WidgetLocation);
			WidgetComponent->SetRelativeRotation(WidgetRotation);
			WidgetComponent->SetWidgetSpace(OverlappedActor->IsA(AOreCharacter::StaticClass()) ? EWidgetSpace::World : EWidgetSpace::Screen);
			
		}
		else if(WidgetComponent)
		{
			// Update the UI
			WidgetComponent->SetVisibility(true);
			UOreGameplayStatics::GetOreGameMode(this)->ShowPrompt(InteractionText);
		}
	}	
}

void UInteractionComponentBase::OnInteractionVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AOreCharacterBase* OverlappedActor = Cast<AOreCharacterBase>(OtherActor))
	{
		UOreGameplayStatics::GetOreGameInstance(GetOwner())->PopInteraction();
	}

	if (WidgetComponent)
	{
		// Update the UI
		WidgetComponent->SetVisibility(false);
		UOreGameplayStatics::GetOreGameMode(this)->HidePrompt();
	}
		
}


// Called when the game starts
void UInteractionComponentBase::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponentBase::OnInteractionVolumeBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UInteractionComponentBase::OnInteractionVolumeEndOverlap);
}
