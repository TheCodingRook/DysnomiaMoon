// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "UI/OreHUD.h"
#include "Components/TextBlock.h"

void UOreHUD::ShowPrompt(FText InText)
{
	if(PromptText)
	{
		SetPromptText(InText);
		PromptText->SetVisibility(ESlateVisibility::Visible);		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Where is my prompt?!"));
	}
}

void UOreHUD::HidePrompt()
{
	if (PromptText)
	{
		PromptText->SetVisibility(ESlateVisibility::Hidden);	
	}
}

void UOreHUD::SetPromptText(FText InText)
{
	PromptText->SetText(InText);
}
