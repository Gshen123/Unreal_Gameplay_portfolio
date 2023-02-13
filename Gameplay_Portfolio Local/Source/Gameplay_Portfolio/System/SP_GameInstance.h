// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularData.h"
#include "Gameplay_Portfolio/System/SP_CoreType.h"
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
    FLevelData GetMenuLevelData() const { return MenuLevelData; }
    TArray<FLevelData> GetLevelsData() const { return LevelsData; }
    void SetStartupLevelData(const FLevelData& Data) { StartupLevelData = Data;}
    void OpenLevel(const UObject* WorldContextObject, EGameModeType Type);
    
    USP_DefaultPartsAsset* GetDefaultMeshParts() const;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ToolTip = "Level names must be unique!"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    TSoftObjectPtr<USP_DefaultPartsAsset> DefaultPartsAssets;
    
    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;

private:
    
    UPROPERTY()
    FLevelData StartupLevelData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess))
    FLevelData MenuLevelData;
};
