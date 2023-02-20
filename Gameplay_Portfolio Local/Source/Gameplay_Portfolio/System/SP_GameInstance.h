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
    virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
    
    FLevelData GetStartupLevelData() const { return StartupLevelData; }
    FLevelData GetMenuLevelData() const { return MenuLevelData; }
    TArray<FLevelData> GetLevelsData() const { return LevelsData; }
    void SetStartupLevelData(const FLevelData& Data) { StartupLevelData = Data;}
    void OpenLevel(const UObject* WorldContextObject, EGameModeType Type, int32 LocalPlayerIndex = 0);
    
    USP_DefaultPartsAsset* GetDefaultMeshParts() const;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ToolTip = "Level names must be unique!"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    TSoftObjectPtr<USP_DefaultPartsAsset> DefaultPartsAssets;
    
    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;

private:

#if WITH_EDITOR
    void TestLoadSaveFile();
#endif
    
    UPROPERTY()
    FLevelData StartupLevelData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess))
    FLevelData MenuLevelData;

#if WITH_EDITORONLY_DATA
    // 타입별 메시에 대한 관리방식 지정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Test, meta = (AllowPrivateAccess = "true", ToolTip = "(빠른 개발 목적) 로드할 파일슬롯명"))
    FString Test_LoadSaveSlotName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Test, meta = (AllowPrivateAccess = "true", ToolTip = "(빠른 개발 목적) 오픈할 레벨 타입"))
    EGameModeType Test_OpenLevelType;
#endif
    
};
