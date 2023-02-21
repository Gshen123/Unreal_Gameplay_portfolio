// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameInstance.h"
#include "SP_AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"
#include "Subsystem/SP_SaveGameSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameInstance, All, All);


FGameInstancePIEResult USP_GameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
    TestLoadSaveFile();
    
    return Super::StartPlayInEditorGameInstance(LocalPlayer, Params);
}

void USP_GameInstance::OpenLevel(const UObject* WorldContextObject, EGameModeType Type, int32 LocalPlayerIndex)
{
    const FLevelData* OpenLevelData = nullptr;
    for (const FLevelData& Data : LevelsData)
    {
        if(Data.Type == Type)
        {
            OpenLevelData = &Data;
            break;
        }
    }
    if(OpenLevelData == nullptr) return;

    // 수명주기가 유지되는 서브시스템의 일부 데이터를 초기화합니다.
    GetLocalPlayerByIndex(LocalPlayerIndex)->GetSubsystem<USP_LocalPlayerMeshManager>()->Deinitialize();
    GetSubsystem<USP_SaveGameSubsystem>()->Deinitialize();
    
    UGameplayStatics::OpenLevel(WorldContextObject, OpenLevelData->LevelName);
}


USP_DefaultPartsAsset* USP_GameInstance::GetDefaultMeshParts() const
{
    if(DefaultPartsAssets.Get() == nullptr) return USP_AssetManager::GetAsset(DefaultPartsAssets);

    return DefaultPartsAssets.Get();
}

#if WITH_EDITOR
void USP_GameInstance::TestLoadSaveFile()
{
    if(!Test_LoadSaveSlotName.IsEmpty() && Test_OpenLevelType != EGameModeType::None)
        GetSubsystem<USP_SaveGameSubsystem>()->LoadSaveGame(Test_LoadSaveSlotName, false,0);
    OpenLevel(GetWorld(), Test_OpenLevelType, 0);
}
#endif