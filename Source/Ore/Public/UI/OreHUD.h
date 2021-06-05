// Copyright 2021. Project Ore developed by CodingRook for the GameDev.TV GameJam of 2021

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelElements/OreLumpBase.h"

#include "OreHUD.generated.h"

// Forward declarations
class UTextBlock;

/**
 * 
 */
UCLASS()
class ORE_API UOreHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void ShowPrompt(FText InText);

	UFUNCTION(BlueprintCallable)
    void HidePrompt();

	UFUNCTION(BlueprintCallable)
	void SetPromptText(FText InText);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AddOnOffText();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateMeteorStrikeCount();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void UpdateGoldShipped();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateParasiteShipped();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateSpacecraftHealth(float InHealth);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowSpacecraftHealthBar();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void HideSpacecraftHealthBar();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GiveInfectionWarning(const FText& InMineType);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void UpdateInfectionsCounter(int Delta);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void UpdateRemainingTime(float InTime);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void UpdateSupplies(float InFuel, float InGold);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PromptText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MeteorCountValue;

	UPROPERTY(BlueprintReadWrite)
	FText OnOffText = FText::FromString("Default");
};
