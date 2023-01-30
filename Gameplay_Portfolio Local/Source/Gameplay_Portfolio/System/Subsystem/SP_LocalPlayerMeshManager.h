// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "MergeComponent.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "Save/SP_SaveData.h"
#include "SP_LocalPlayerMeshManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMeshWidgetUpdated, FPrimaryAssetType);
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_LocalPlayerMeshManager : public ULocalPlayerSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void AddMergeComponent(UMergeComponent* Component);
    
    UFUNCTION(BlueprintCallable)
    TArray<UMergeComponent*> GetMergeComponents();

    UFUNCTION(BlueprintCallable)
    void ReplaceItemInSlot(USP_ModularItemBase* Item);
    
    UFUNCTION(BlueprintCallable)
    void UpdateMesh(UMergeComponent* MergeComponent);

    UFUNCTION()
    void FindAndAddMeshItemData(FPrimaryAssetType Type, FName Name);
    
    void SetMorphTarget(FString MorphTargetName, float Value);

    void AllUpdateMorphTarget();

    void ResetMorphTargetData();

    FModularPartsSlotData* GetPartsSlot();

    FPlayerMeshData SaveMeshData() const;
    
    FMeshWidgetUpdated WidgetUpdated;
    
protected:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION()
    void WearItem(USP_ModularItemBase* Item);
    
private:
    UFUNCTION()
    void UpdateWidget(FPrimaryAssetType Type) const;

    USP_DefaultPartsAsset* GetDefaultParts() const;
    
    UPROPERTY()
    TArray<UMergeComponent*> MergeComponents;
    
    UPROPERTY()
    TArray<USkeletalMesh*> Meshes;

    UPROPERTY()
    USP_DefaultPartsAsset* DefaultPartAsset;

    UPROPERTY()
    FModularPartsSlotData ModularPartsSlot;

    UPROPERTY()
    TMap<FName, float> MorphTargetData;

    TMap<FPrimaryAssetType, FName> MeshItemData;
};
