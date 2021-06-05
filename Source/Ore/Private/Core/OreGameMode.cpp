// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/OreGameMode.h"
#include "Core/OreGameplayStatics.h"
#include "UI/OreHUD.h"
#include "UObject/ConstructorHelpers.h"

AOreGameMode::AOreGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AOrePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ProjectOre/Player/BP_AstroMiner3P"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AOreGameMode::ShowPrompt(FText InText)
{
	if (MainHUD)
	{
		MainHUD->ShowPrompt(InText);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("There is no HUD defined to populate UI prompts!"));
	}
	
}

void AOreGameMode::HidePrompt()
{
	MainHUD->HidePrompt();
	MainHUD->SetPromptText(FText::GetEmpty());
}

void AOreGameMode::OnMeteorCrashed()
{
	if(MeteorStrikeCount < MaxMeteorStrikes -1)
	{
		++MeteorStrikeCount;
		MainHUD->UpdateMeteorStrikeCount();
	}
	else
	{
		UOreGameplayStatics::SetGamePaused(this, true);
		UOreGameplayStatics::OpenLevel(this, TEXT("MainMenu"));
	}
}
