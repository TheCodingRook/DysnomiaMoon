// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * Custom class for interaction widgets in Ore
 */
UCLASS()
class ORE_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void DisplayPrompt();
	
};
