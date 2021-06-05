// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021


#include "Core/OreGameplayStatics.h"

UOreGameInstance* UOreGameplayStatics::GetOreGameInstance(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World->GetGameInstanceChecked<UOreGameInstance>();
}

AOreGameMode* UOreGameplayStatics::GetOreGameMode(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return Cast<AOreGameMode>(GetGameMode(World));
}

AOrePlayerController* UOreGameplayStatics::GetOrePlayerController(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return Cast<AOrePlayerController>(World->GetFirstPlayerController());
}

AOreCharacter* UOreGameplayStatics::GetOreCharacter(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if(AOrePlayerController* OrePlayerController = GetOrePlayerController(World))
	{
		return Cast<AOreCharacter>(OrePlayerController->GetCharacter());
	}
	return nullptr;
}

AOreCharacter3P* UOreGameplayStatics::GetOreCharacter3P(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if(AOrePlayerController* OrePlayerController = GetOrePlayerController(World))
	{
		return Cast<AOreCharacter3P>(OrePlayerController->GetCharacter());
	}
	return nullptr;
}


