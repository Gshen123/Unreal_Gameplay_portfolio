// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay_Portfolio/System//SP_CoreType.h"
#include "SP_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    FLevelData GetStartupLevelData() const { return StartupLevelData; }
    void SetStartupLevelData(const FLevelData& Data) { StartupLevelData = Data;}

    TArray<FLevelData> GetLevelsData() const { return LevelsData; }

    void ToggleVolume();

    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ToolTip = "Level names must be unique!"))
    TArray<FLevelData> LevelsData;
    
    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;

private:
    UPROPERTY()
    FLevelData StartupLevelData;
};
