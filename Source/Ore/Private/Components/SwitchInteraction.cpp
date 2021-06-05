// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "Components/SwitchInteraction.h"
#include "UObject/ConstructorHelpers.h"
#include "Core/OreGameplayStatics.h"
#include "LevelElements/OreBuildingBase.h"
#include "UI/OreHUD.h"
#include "LevelElements/OrePipeline.h"


USwitchInteraction::USwitchInteraction()
{
	InteractionText = FText::FromString("Switch ").ToUpper(); // Space in the text here so we can append the words on/off etc.
	static ConstructorHelpers::FObjectFinder<USoundBase> SwitchSoundAsset(TEXT("/Game/ProjectOre/Audio/A_Switch"));
	SwitchSound = SwitchSoundAsset.Object;
}

void USwitchInteraction::ExecuteInteraction(AOrePlayerController* Instigator)
{
	/** Don't call the Super here because we want to deal with UI a different way */
	//Super::ExecuteInteraction(Instigator); 

	UGameplayStatics::PlaySoundAtLocation(this, SwitchSound, GetOwner()->GetActorLocation());
	if(AOreBuildingBase* Building = Cast<AOreBuildingBase>(GetOwner()))
	{
		if(Building->GetLocationType() != ELocationType::PowerPlant)
		{
			// Toggle the switch 
			Building->OnSwitchToggled(Building->IsSwitchedOn() ? false : true);
			UOreGameplayStatics::GetOreGameMode(this)->MainHUD->OnOffText =  Building->IsSwitchedOn() ? FText::FromString("OFF") : FText::FromString("ON");
			UOreGameplayStatics::GetOreGameMode(this)->MainHUD->AddOnOffText();
			
		}
		
	}
	else if(AOrePipeline* Pipeline = Cast<AOrePipeline>(GetOwner()))
	{
		// Toggle the switch 
		Pipeline->OnSwitchToggled(Pipeline->IsSwitchedOn() ? false : true);
		UOreGameplayStatics::GetOreGameMode(this)->MainHUD->OnOffText =  Pipeline->IsSwitchedOn() ? FText::FromString("OFF") : FText::FromString("ON");
		UOreGameplayStatics::GetOreGameMode(this)->MainHUD->AddOnOffText();
	}
}

void USwitchInteraction::OnInteractionVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnInteractionVolumeBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(AOreBuildingBase* Building = Cast<AOreBuildingBase>(GetOwner()))
	{
		if(Building->GetLocationType() != ELocationType::PowerPlant)
		{
			UOreGameplayStatics::GetOreGameMode(this)->MainHUD->OnOffText =  Building->IsSwitchedOn() ? FText::FromString("OFF") : FText::FromString("ON");
			UOreGameplayStatics::GetOreGameMode(this)->MainHUD->AddOnOffText();
			
		}
		
	}
	else if(AOrePipeline* Pipeline = Cast<AOrePipeline>(GetOwner()))
	{
		UOreGameplayStatics::GetOreGameMode(this)->MainHUD->OnOffText =  Pipeline->IsSwitchedOn() ? FText::FromString("OFF") : FText::FromString("ON");
		UOreGameplayStatics::GetOreGameMode(this)->MainHUD->AddOnOffText();
		
	}

}

void USwitchInteraction::OnInteractionVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnInteractionVolumeEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	InteractionText = FText::FromString("Switch ").ToUpper(); // Space in the text here so we can append the words on/off etc.
			
}
