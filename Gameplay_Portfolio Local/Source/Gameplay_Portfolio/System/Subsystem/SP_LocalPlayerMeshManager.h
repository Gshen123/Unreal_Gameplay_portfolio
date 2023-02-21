// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/SP_MergeComponent.h"
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
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    void MeshDataInit(FSaveMeshData LoadPlayerMeshData, TMap<EMergePawnType, FSaveMeshData> LoadNPCMeshData);
    bool IsInit() const;
    FSaveMeshData GetMeshData(EMergePawnType PawnType);
    
    void AddMergeComponent(USP_MergeComponent* Component, EMergePawnType PawnType);
    TArray<USP_MergeComponent*> FindMergeComponent(EMergePawnType Key) const;
    
    FSaveMeshData* GetPlayerMeshData();
    void WearItem(const USP_ModularItemBase* Item, EMergePawnType PawnType, FName DefaultItemName);
    void ReplaceItemInSlot(const USP_ModularItemBase* Item, EMergePawnType PawnType, FName DefaultItemName);
    void FindAndAddMeshItemData(FPrimaryAssetType Type, FString Name, EMergePawnType PawnType);

    void AllUpdateMaterial(EMergePawnType PawnType);
    void UpdateMaterial(const USP_MergeComponent* MergeComponent);
    void FindAndAddMaterialData(int32 Index, FName ParamName, FLinearColor Value, UMaterialInstance* MaterialInstance, EMergePawnType PawnType);

    void LoadMorphTarget(EMergePawnType PawnType, bool Reset = false);
    void UpdateMorphTarget(const USP_MergeComponent* Component, EMergePawnType PawnType, bool Reset = false);
    void FindAndAddMorphTarget(FString MorphTargetName, float Value, EMergePawnType PawnType);
    
    void UpdateAnimation(UAnimationAsset* Asset, EMergePawnType PawnType) const;
    
    FMeshWidgetUpdated WidgetUpdated;

protected:
    void UpdateMesh(USP_MergeComponent* MergeComponent);
    
private:
    void UpdateWidget(FPrimaryAssetType Type) const;

    USP_DefaultPartsAsset* GetDefaultParts() const;

    UPROPERTY()
    USP_DefaultPartsAsset* DefaultPartAsset;

    TMultiMap<EMergePawnType, USP_MergeComponent*> MergeComponents;

    UPROPERTY()
    TArray<USkeletalMesh*> Meshes;
    
    UPROPERTY()
    FSaveMeshData PlayerMeshData;
    
    UPROPERTY()
    TMap<EMergePawnType, FSaveMeshData> NPCMeshData;

    UPROPERTY()
    bool bIsInit = false;
};

