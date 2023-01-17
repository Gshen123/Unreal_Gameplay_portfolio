// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_ModularCharacterData.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularData.h"
#include "SP_ModularItemBase.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSP_ModularItemData
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "복장|타입")
    FPrimaryAssetType ItemType;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName= "신체 가림여부", Category = "복장|기본")
    bool OverlapBody = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName= "복장명", Category = "복장|기본")
    FText DisplayName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName= "메시", Category = "복장|메시")
    TArray<TSoftObjectPtr<USkeletalMesh>> Meshes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "복장|착용 조건", DisplayName = "아이템 착용가능 조건")
    FModularItemConditions ItemConditions;

    UPROPERTY()
    int32 OccupiedParts;
};

UCLASS(Abstract, Blueprintable)
class GAMEPLAY_PORTFOLIO_API USP_ModularItemBase : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:

    USP_ModularItemBase(){};

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSP_ModularItemData Data;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    FText GetDisplayName() const;
};


inline FPrimaryAssetId USP_ModularItemBase::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(Data.ItemType, GetFName());
}

inline FText USP_ModularItemBase::GetDisplayName() const
{
    return Data.DisplayName;
}