// Scope Portfolio. All rights reserved


#include "SP_LocalPlayerMeshManager.h"

#include "SP_AssetManager.h"
#include "SP_GameInstance.h"
#include "ModularCharacterSetup/SP_CharacterItemWidget.h"
#include "ModularCharacterSystem/SP_MergeStruct.h"
#include "ModularCharacterSystem/SP_MergeUtil.h"

DEFINE_LOG_CATEGORY_STATIC(LogLocalPlayerMeshManager, All, All);

void USP_LocalPlayerMeshManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    DefaultPartAsset = GetDefaultParts();
}

void USP_LocalPlayerMeshManager::Deinitialize()
{
    MeshData.Empty();
    Super::Deinitialize();
}

void USP_LocalPlayerMeshManager::LoadMeshData(FPlayerMeshData LoadData)
{
    MeshData = LoadData;
    if(MeshData.IsEmpty()) return;

    AllUpdateMesh();
    AllUpdateMaterial();
    AllUpdateMorphTarget();
}

void USP_LocalPlayerMeshManager::UpdateWidget(FPrimaryAssetType Type) const
{
    WidgetUpdated.Broadcast(Type);
}

USP_DefaultPartsAsset* USP_LocalPlayerMeshManager::GetDefaultParts() const
{
    auto GI = GetWorld()->GetGameInstance<USP_GameInstance>();
    check(GI != nullptr);
    return GI->GetDefaultMeshParts();
}

void USP_LocalPlayerMeshManager::AddMergeComponent(USP_MergeComponent* Component)
{
    MergeComponents.AddUnique(Component);
}

TArray<USP_MergeComponent*> USP_LocalPlayerMeshManager::GetMergeComponents()
{
    return MergeComponents;
}

void USP_LocalPlayerMeshManager::UpdateMesh(USP_MergeComponent* MergeComponent)
{
    Meshes.Reset();
    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData.ModularPartsSlot.Body);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr) SKMesh = USP_AssetManager::GetAsset(Mesh);     
                Meshes.Add(SKMesh);
            }
        }
        if(MeshData.ModularPartsSlot.BodyShare.Num() == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Body);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData.ModularPartsSlot.Arm);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr) SKMesh = USP_AssetManager::GetAsset(Mesh);     
                Meshes.Add(SKMesh);
            }
        }
        if(MeshData.ModularPartsSlot.ArmShare.Num() == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Arm);  
            Meshes.Add(SKMesh);
            SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Hand);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData.ModularPartsSlot.Leg);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr) SKMesh = USP_AssetManager::GetAsset(Mesh);     
                Meshes.Add(SKMesh);
            }
        }
        if(MeshData.ModularPartsSlot.LegShare.Num() == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Leg);  
            Meshes.Add(SKMesh);
            SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Feet);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData.ModularPartsSlot.Suit);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr) SKMesh = USP_AssetManager::GetAsset(Mesh);     
                Meshes.Add(SKMesh);
            }
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData.ModularPartsSlot.Head);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr) SKMesh = USP_AssetManager::GetAsset(Mesh);     
                Meshes.Add(SKMesh);
            }
        }
    }
    
    USkeleton* Skeleton = USP_AssetManager::GetAsset(DefaultPartAsset->Skeleton);
    FSkeletalMeshMergeParamsScope MeshMergeParams;
    MeshMergeParams.Skeleton = Skeleton;
    MeshMergeParams.MeshesToMerge = Meshes;
    USkeletalMesh* MergedMesh = nullptr;
    if(Meshes.Num() > 1) MergedMesh = USP_MergeUtil::MergeMeshes(MeshMergeParams);

    if(MergedMesh != nullptr || Meshes.Num() == 1)
    {
        if(MeshData.ModularPartsSlot.HeadShare.Num() == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Head);
            MergeComponent->GetOwnerMesh()->SetSkeletalMesh(SKMesh, false);

            if(MergedMesh != nullptr) MergeComponent->SetSkeletalMeshAsset(MergedMesh);
            else MergeComponent->SetSkeletalMeshAsset(Meshes[0]);
            
            MergeComponent->SetLeaderPoseComponent(MergeComponent->GetOwnerMesh());
            AllUpdateMorphTarget();
            UpdateMaterial(MergeComponent);
        }
        else
        {
            if(MergedMesh != nullptr) MergeComponent->GetOwnerMesh()->SetSkeletalMeshAsset(MergedMesh);
            else MergeComponent->GetOwnerMesh()->SetSkeletalMeshAsset(Meshes[0]);
            MergeComponent->SetSkeletalMeshAsset(nullptr);
        }
    }
}

void USP_LocalPlayerMeshManager::AllUpdateMesh()
{
    for (const auto MergeComponent : MergeComponents) UpdateMesh(MergeComponent);
}


void USP_LocalPlayerMeshManager::AllUpdateMaterial()
{
    for (const auto MergeComponent : MergeComponents) UpdateMaterial(MergeComponent);
}

void USP_LocalPlayerMeshManager::UpdateMaterial(USP_MergeComponent* MergeComponent)
{
    for (auto iter = MeshData.MaterialData.CreateConstIterator(); iter; ++iter)
    {
        FMaterialData* Data = MeshData.MaterialData.Find(iter.Key());
        UMaterialInstanceDynamic* HeadDynamicMesh =  MergeComponent->GetOwnerMesh()->CreateDynamicMaterialInstance(iter.Key(), Data->MaterialInstance);
        for (auto it= Data->ParamData.CreateConstIterator(); it; ++it)
        {
            HeadDynamicMesh->SetVectorParameterValue(it.Key(), it.Value());
        }
    }
}

void USP_LocalPlayerMeshManager::FindAndAddMeshItemData(FPrimaryAssetType Type, FName Name)
{
    if(MeshData.MeshItemData.Find(Type))
    {
        MeshData.MeshItemData.Remove(Type);
        MeshData.MeshItemData.Compact();
        MeshData.MeshItemData.Shrink();
        MeshData.MeshItemData.Add(Type, Name);
    }
    else MeshData.MeshItemData.Add(Type, Name);
}

void USP_LocalPlayerMeshManager::FindAndAddMaterialData(int32 Index, FName ParamName, FLinearColor Value, UMaterialInstance* MaterialInstance)
{
    if(const auto PrevData = MeshData.MaterialData.Find(Index))
    {
        PrevData->ParamData.Add(ParamName, Value);
    }
    else
    {
        FMaterialData NewData;
        NewData.MaterialInstance = MaterialInstance;
        NewData.ParamData.Add(ParamName, Value);
        MeshData.MaterialData.Add(Index, NewData);
    }
}

void USP_LocalPlayerMeshManager::WearItem(USP_ModularItemBase* Item)
{
    if(Item->Data.ItemType == USP_AssetManager::Module_BodyType)
    {
        MeshData.ModularPartsSlot.Body = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData.ModularPartsSlot.BodyShare.Num() > 0)
            {
                if(MeshData.ModularPartsSlot.BodyShare.Contains(USP_AssetManager::Module_BodyType)) MeshData.ModularPartsSlot.BodyShare.Remove(USP_AssetManager::Module_BodyType);
            }
        }
        else MeshData.ModularPartsSlot.BodyShare.AddUnique(USP_AssetManager::Module_BodyType);
        if(!Item->Data.DisplayName.EqualTo(FText::FromString("None"))) UpdateWidget(USP_AssetManager::Module_SuitType);
        return;
    }

    if(Item->Data.ItemType  == USP_AssetManager::Module_HeadType)
    {
        MeshData.ModularPartsSlot.Head = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData.ModularPartsSlot.HeadShare.Num() > 0)
            {
                if(MeshData.ModularPartsSlot.HeadShare.Contains(USP_AssetManager::Module_HeadType)) MeshData.ModularPartsSlot.HeadShare.Remove(USP_AssetManager::Module_HeadType);
            }
        }
        else MeshData.ModularPartsSlot.HeadShare.AddUnique(USP_AssetManager::Module_HeadType);
        return;
    }
    
    if(Item->Data.ItemType  == USP_AssetManager::Module_FeetAndLegsType)
    {
        MeshData.ModularPartsSlot.Leg = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData.ModularPartsSlot.LegShare.Num() > 0)
            {
                if(MeshData.ModularPartsSlot.LegShare.Contains(USP_AssetManager::Module_FeetAndLegsType)) MeshData.ModularPartsSlot.LegShare.Remove(USP_AssetManager::Module_FeetAndLegsType);
            }
        }
        else MeshData.ModularPartsSlot.LegShare.AddUnique(USP_AssetManager::Module_FeetAndLegsType);
        if(!Item->Data.DisplayName.EqualTo(FText::FromString("None"))) UpdateWidget(USP_AssetManager::Module_SuitType);
        return;
    }

    if(Item->Data.ItemType  == USP_AssetManager::Module_HandAndArmType)
    {
        MeshData.ModularPartsSlot.Arm = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData.ModularPartsSlot.ArmShare.Num() > 0)
            {
                if(MeshData.ModularPartsSlot.ArmShare.Contains(USP_AssetManager::Module_HandAndArmType)) MeshData.ModularPartsSlot.ArmShare.Remove(USP_AssetManager::Module_HandAndArmType);
            }
        }
        else MeshData.ModularPartsSlot.ArmShare.AddUnique(USP_AssetManager::Module_HandAndArmType);
        if(!Item->Data.DisplayName.EqualTo(FText::FromString("None"))) UpdateWidget(USP_AssetManager::Module_SuitType);
        return;
    }

    if(Item->Data.ItemType  == USP_AssetManager::Module_SuitType)
    {
        MeshData.ModularPartsSlot.Suit = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData.ModularPartsSlot.BodyShare.Num() > 0)
                if(MeshData.ModularPartsSlot.BodyShare.Contains(USP_AssetManager::Module_SuitType))
                    MeshData.ModularPartsSlot.BodyShare.Remove(USP_AssetManager::Module_SuitType);
            if(MeshData.ModularPartsSlot.ArmShare.Num() > 0)
                if(MeshData.ModularPartsSlot.ArmShare.Contains(USP_AssetManager::Module_SuitType))
                    MeshData.ModularPartsSlot.ArmShare.Remove(USP_AssetManager::Module_SuitType);
            if(MeshData.ModularPartsSlot.LegShare.Num() > 0)
                if(MeshData.ModularPartsSlot.LegShare.Contains(USP_AssetManager::Module_SuitType))
                    MeshData.ModularPartsSlot.LegShare.Remove(USP_AssetManager::Module_SuitType);
        }
        else
        {
            MeshData.ModularPartsSlot.BodyShare.AddUnique(USP_AssetManager::Module_SuitType);
            MeshData.ModularPartsSlot.ArmShare.AddUnique(USP_AssetManager::Module_SuitType);
            MeshData.ModularPartsSlot.LegShare.AddUnique(USP_AssetManager::Module_SuitType);
            UpdateWidget(USP_AssetManager::Module_BodyType);
            UpdateWidget(USP_AssetManager::Module_HandAndArmType);
            UpdateWidget(USP_AssetManager::Module_FeetAndLegsType);
        }
    }
}

void USP_LocalPlayerMeshManager::ReplaceItemInSlot(USP_ModularItemBase* Item)
{
    WearItem(Item);

    if(MeshData.ModularPartsSlot.Head == nullptr || MeshData.ModularPartsSlot.Arm == nullptr || MeshData.ModularPartsSlot.Body == nullptr ||
       MeshData.ModularPartsSlot.Leg == nullptr || MeshData.ModularPartsSlot.Suit == nullptr) return;
    
    for(const auto Component : MergeComponents) UpdateMesh(Component);
}

void USP_LocalPlayerMeshManager::SetMorphTarget(FString MorphTargetName, float Value)
{
    const FName TargetName = FName(*MorphTargetName);
    for (const auto Component : MergeComponents)
    {
        Component->SetOwnerMorphTarget(TargetName, Value, false);
    }
    
    if(MeshData.MorphTargetData.RemoveAndCopyValue(TargetName, Value))
    {
        MeshData.MorphTargetData.Compact();
        MeshData.MorphTargetData.Shrink();
        MeshData.MorphTargetData.Add(TargetName, Value);
        UE_LOG(LogLocalPlayerMeshManager, Log, TEXT("RemoveAndAdd : %s"), *MorphTargetName);
    }
    else
    {
        MeshData.MorphTargetData.Add(TargetName, Value);
        UE_LOG(LogLocalPlayerMeshManager, Log, TEXT("Add : %s"), *MorphTargetName);
    }
}

void USP_LocalPlayerMeshManager::AllUpdateMorphTarget()
{
    if(MeshData.MorphTargetData.Num() == 0) return;
    
    for (const auto Component : MergeComponents)
    {
        Component->ClearMorphTarget();
        for (const auto Data : MeshData.MorphTargetData)
        {
            Component->SetOwnerMorphTarget(Data.Key, Data.Value, false);
        }
    }
}

void USP_LocalPlayerMeshManager::ResetMorphTargetData()
{
    for (const auto Component : MergeComponents)
    {
        for (const auto Data : MeshData.MorphTargetData)
        {
            Component->ClearMorphTarget();
            Component->SetOwnerMorphTarget(Data.Key, 0, false);
            UE_LOG(LogLocalPlayerMeshManager, Log, TEXT("Reset : %s"), *Data.Key.ToString());
        }
    }
    
    MeshData.MorphTargetData.Empty();
}

void USP_LocalPlayerMeshManager::UpdateAnimation(UAnimationAsset* Asset)
{
    for (const auto Component : MergeComponents) Component->UpdateAnimation(Asset);
}

FPlayerMeshData* USP_LocalPlayerMeshManager::GetMeshData()
{
    return &MeshData;
}