// Scope Portfolio. All rights reserved


#include "SP_PlayerState.h"

#include "SP_AssetManager.h"
#include "SP_PlayerCharacter.h"
#include "SP_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All);

void ASP_PlayerState::BeginPlay()
{
    Super::BeginPlay();
}

USP_LocalPlayerMeshManager* ASP_PlayerState::GetLocalPlayerMeshManager() const
{
    return GetPlayerController()->GetLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>();
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

void ASP_PlayerState::SavePlayerState(USP_SaveGame* SaveObject, EGameModeType Mode) const
{
    if (SaveObject)
    {
        FPlayerSaveData SaveData;
        // 플레이어의 저장 정보를 업데이트합니다

        SaveData.PlayerID = GetUniqueId().ToString();
        SaveData.PlayTime= UGameplayStatics::GetRealTimeSeconds(GetPlayerController()) * ETimespan::TicksPerSecond;

        if(Mode == EGameModeType::InGame || Mode == EGameModeType::CharacterSetup)
            SaveData.PlayerMeshData = *GetLocalPlayerMeshManager()->GetPlayerMeshData();
        
        if(Mode == EGameModeType::InGame)
            if (const APawn* MyPawn = GetPawn())
            {
                SaveData.Location = MyPawn->GetActorLocation();
                SaveData.Rotation = MyPawn->GetActorRotation();
                SaveData.bResumeAtTransform = true;
            }
        
        SaveObject->PlayerSaveData.Add(SaveData);
    }
}

void ASP_PlayerState::LoadPlayerState(USP_SaveGame* SaveObject, EGameModeType Mode)
{
    if (SaveObject)
    {
        if(Mode == EGameModeType::InGame)
            NPCMeshData = SaveObject->NPCMeshData;
        
        if (const FPlayerSaveData* FoundData = SaveObject->GetPlayerData(this))
        {
            if(Mode == EGameModeType::InGame || Mode == EGameModeType::CharacterSetup)
                PlayerMeshData = FoundData->PlayerMeshData;
        }
        
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Could not find SaveGame data for player id '%i'."), GetPlayerId());
        }
    }
}

void ASP_PlayerState::UpdateMergeComponent(USP_MergeComponent* Component, EMergePawnType PawnType) const
{
    const auto MeshManager = GetLocalPlayerMeshManager();
    MeshManager->IsInit() ? nullptr : MeshManager->MeshDataInit(PlayerMeshData, NPCMeshData);
    MeshManager->AddMergeComponent(Component, PawnType);
}
