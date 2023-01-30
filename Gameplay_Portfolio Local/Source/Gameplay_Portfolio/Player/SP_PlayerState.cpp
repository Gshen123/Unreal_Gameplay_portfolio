// Scope Portfolio. All rights reserved


#include "SP_PlayerState.h"

#include "SP_AssetManager.h"
#include "SP_PlayerCharacter.h"
#include "SP_GameInstance.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All);

void ASP_PlayerState::BeginPlay()
{
    Super::BeginPlay();
}


int32 ASP_PlayerState::GetKillsNum() const
{
    return KillCount;
}

int32 ASP_PlayerState::GetCoinsNum() const
{
    return CoinCount;
}

int32 ASP_PlayerState::GetLevelNum() const
{
    return LevelCount;
}

void ASP_PlayerState::SavePlayerState(USP_SaveGame* SaveObject) const
{
    if (SaveObject)
    {
        FPlayerSaveData SaveData;
        // 플레이어의 저장 정보를 업데이트합니다

        SaveData.PlayerID = GetUniqueId().ToString();
        SaveData.MeshData = GetPlayerController()->GetLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>()->SaveMeshData();
        
        if (APawn* MyPawn = GetPawn())
        {
            SaveData.Location = MyPawn->GetActorLocation();
            SaveData.Rotation = MyPawn->GetActorRotation();
            SaveData.bResumeAtTransform = true;
        }
		
        SaveObject->PlayerSaveDatas.Add(SaveData);
    }
}

void ASP_PlayerState::LoadPlayerState(USP_SaveGame* SaveObject)
{
    if (SaveObject)
    {
        FPlayerSaveData* FoundData = SaveObject->GetPlayerData(this);
        if (FoundData)
        {
            MeshData = FoundData->MeshData;
            //플레이어 스테이트 정보 갱신
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Could not find SaveGame data for player id '%i'."), GetPlayerId());
        }
    }
}

FPlayerMeshData ASP_PlayerState::GetMeshData()
{
    return MeshData;
}
