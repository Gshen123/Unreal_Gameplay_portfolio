// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameInstance.h"

#include "SP_AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"
#include "Subsystem/SP_SaveGameSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameInstance, All, All);

void USP_GameInstance::OpenLevel(const UObject* WorldContextObject, EGameModeType Type)
{
    const FLevelData* OpenLevelData = nullptr;
    for (FLevelData& Data : LevelsData)
    {
        if(Data.Type == Type)
        {
            OpenLevelData = &Data;
            break;
        }
    }
    if(OpenLevelData == nullptr) return;
    SetStartupLevelData(*OpenLevelData);

    // 수명주기가 유지되는 서브시스템의 일부 데이터를 초기화합니다.
    for(auto LocalPlayer : GetLocalPlayers()) LocalPlayer->GetSubsystem<USP_LocalPlayerMeshManager>()->Deinitialize();
    GetSubsystem<USP_SaveGameSubsystem>()->Deinitialize();
    
    UGameplayStatics::OpenLevel(WorldContextObject, OpenLevelData->LevelName);
}

USP_DefaultPartsAsset* USP_GameInstance::GetDefaultMeshParts() const
{
    if(DefaultPartsAssets.Get() == nullptr) return USP_AssetManager::GetAsset(DefaultPartsAssets);

    return DefaultPartsAssets.Get();
}
