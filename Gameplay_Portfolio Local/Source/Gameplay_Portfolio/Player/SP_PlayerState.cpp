// Scope Portfolio. All rights reserved


#include "SP_PlayerState.h"

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
        // coin = saveobject.coin;
        
        SaveData.PlayerID = GetUniqueId().ToString();
        
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
            //플레이어 스테이트 정보 갱신
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Could not find SaveGame data for player id '%i'."), GetPlayerId());
        }
    }
}

FModularPartsSlotData ASP_PlayerState::GetPartsData() const
{
    return PartsData;
}
