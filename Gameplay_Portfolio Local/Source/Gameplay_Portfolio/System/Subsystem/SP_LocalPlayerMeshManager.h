// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_MergeComponent.h"
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
    virtual void Deinitialize() override;

    UFUNCTION()
    void LoadMeshData(FPlayerMeshData LoadData);
    
    UFUNCTION(BlueprintCallable)
    void AddMergeComponent(USP_MergeComponent* Component);
    
    UFUNCTION(BlueprintCallable)
    TArray<USP_MergeComponent*> GetMergeComponents();

    UFUNCTION(BlueprintCallable)
    void ReplaceItemInSlot(USP_ModularItemBase* Item);
    
    UFUNCTION(BlueprintCallable)
    void UpdateMesh(USP_MergeComponent* MergeComponent);

    UFUNCTION()
    void AllUpdateMesh();
        
    UFUNCTION()
    void AllUpdateMaterial();
    
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

    FPlayerMeshData* GetMeshData();
    
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
    USP_DefaultPartsAsset* DefaultPartAsset;

    UPROPERTY()
    TArray<USP_MergeComponent*> MergeComponents;

    UPROPERTY()
    TArray<USkeletalMesh*> Meshes;
    
    UPROPERTY()
    FPlayerMeshData MeshData;
};