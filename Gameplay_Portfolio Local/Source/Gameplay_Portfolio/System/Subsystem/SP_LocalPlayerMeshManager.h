// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_MergeComponent.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "ModularCharacterSetup/SP_CharacterItemWidget.h"
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
    void AddMergeComponent(USP_MergeComponent* Component);

    virtual void Deinitialize() override;
    
    UFUNCTION(BlueprintCallable)
    TArray<USP_MergeComponent*> GetMergeComponents();

    UFUNCTION(BlueprintCallable)
    void ReplaceItemInSlot(USP_ModularItemBase* Item);
    
    UFUNCTION(BlueprintCallable)
    void UpdateMesh(USP_MergeComponent* MergeComponent);

    UFUNCTION()
    void AllUpdateMaterail();
    
    UFUNCTION()
    void UpdateMaterial(USP_MergeComponent* MergeComponent);
    
    UFUNCTION()
    void FindAndAddMeshItemData(FPrimaryAssetType Type, FName Name);

    UFUNCTION()
    void FindAndAddMaterialData(int32 Index, FName ParamName, FLinearColor Value, UMaterialInstance* MaterialInstance);
    
    void SetMorphTarget(FString MorphTargetName, float Value);

    void AllUpdateMorphTarget();

    void ResetMorphTargetData();

    void UpdateAnimation(UAnimationAsset* Asset);

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
    TArray<USP_MergeComponent*> MergeComponents;
    
    UPROPERTY()
    TArray<USkeletalMesh*> Meshes;

    UPROPERTY()
    USP_DefaultPartsAsset* DefaultPartAsset;

    UPROPERTY()
    FModularPartsSlotData ModularPartsSlot;

    UPROPERTY()
    TMap<FName, float> MorphTargetData;

    TMap<FPrimaryAssetType, FName> MeshItemData;

    TMap<int32, FMaterialData> MaterialData; 
};
