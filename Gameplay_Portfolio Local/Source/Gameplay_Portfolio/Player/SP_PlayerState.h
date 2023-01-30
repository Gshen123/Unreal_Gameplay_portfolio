// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Save/SP_SaveGame.h"
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
    void SavePlayerState(USP_SaveGame* SaveObject) const;

    UFUNCTION()
    void LoadPlayerState(USP_SaveGame* SaveObject);

    UFUNCTION()
    FPlayerMeshData GetMeshData();

protected:
    
    virtual void BeginPlay() override;
    
private:

    int32 KillCount = 0;

    int32 CoinCount = 0;

    int32 LevelCount = 0;

    UPROPERTY()
    FPlayerMeshData MeshData;
};
