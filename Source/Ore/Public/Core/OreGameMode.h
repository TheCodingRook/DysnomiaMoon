// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OreGameMode.generated.h"

/**
* Custom enumeration type to explain why game is over
*/
UENUM(BlueprintType)
enum class EGameOverReason : uint8
{
	Meteors UMETA(DisplayName = "Too many meteors"),
    Parasite UMETA(DisplayName = "Too much parasite shipped"),
};


// Forward declarations
class UOreHUD;

UCLASS(minimalapi)
class AOreGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOreGameMode();

	UFUNCTION(BlueprintCallable)
	void ShowPrompt(FText InText);

	UFUNCTION(BlueprintCallable)
    void HidePrompt();

	UFUNCTION(BlueprintCallable)
	void OnMeteorCrashed();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UOreHUD* MainHUD;

	// How many meteors have crashed on the surface?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int MeteorStrikeCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxMeteorStrikes = 10;

	// How much gold have we shipped back to Earth??
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float GoldShipped;

	// How much gold have we shipped back to Earth??
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ParasiteShipped;

};



