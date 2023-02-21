// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "GameFramework/PlayerState.h"
#include "Save/SP_SaveGame.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"
#include "SP_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_PlayerState : public APlayerState
{
    GENERATED_BODY()

public:

    int32 GetKillsNum() const;
    int32 GetCoinsNum() const;
    int32 GetLevelNum() const;

    UFUNCTION()
    void SavePlayerState(USP_SaveGame* SaveObject, EGameModeType Mode) const;

    UFUNCTION()
    void LoadPlayerState(USP_SaveGame* SaveObject, EGameModeType Mode);

    UFUNCTION()
    void UpdateMergeComponent(USP_MergeComponent* Component, EMergePawnType PawnType) const;

    UFUNCTION()
    EGameModeType GetCurrentGameModeType() const { return CurrentModeType;}

protected:
    
    virtual void BeginPlay() override;
    
private:

    UFUNCTION()
    USP_LocalPlayerMeshManager* GetLocalPlayerMeshManager() const;
    
    int32 KillCount = 0;

    int32 CoinCount = 0;

    int32 LevelCount = 0;

    UPROPERTY()
    FSaveMeshData PlayerMeshData;

    UPROPERTY()
    TMap<EMergePawnType, FSaveMeshData> NPCMeshData;

    UPROPERTY()
    EGameModeType CurrentModeType = EGameModeType::None;
};
