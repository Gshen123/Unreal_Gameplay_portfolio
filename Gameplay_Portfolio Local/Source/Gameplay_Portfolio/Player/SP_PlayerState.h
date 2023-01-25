// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularData.h"
#include "Save/SP_SaveGame.h"
#include "SP_PlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FMergedMeshUpdate)
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
    USkeletalMesh* UpdateMesh();

    void ReplaceItemInSlot(USP_ModularItemBase* Item);

    FModularPartsSlotData* GetPartsSlot();

    bool CheckAndWear(int32 bitmask);

    void SetWear(int32 bitmask, bool Unwear = false);

    FMergedMeshUpdate MeshUpdated;
    
private:

    int32 KillCount = 0;

    int32 CoinCount = 0;

    int32 LevelCount = 0;
    
    UPROPERTY()
    TArray<USkeletalMesh*> Meshes;

    UPROPERTY()
    USP_DefaultPartsAsset* DefaultPartAsset;

    UPROPERTY()
    FModularPartsSlotData ModularPartsSlot;
    
    UPROPERTY()
    int32 WearStatus = 0;

    USP_DefaultPartsAsset* GetDefaultParts() const;
};
