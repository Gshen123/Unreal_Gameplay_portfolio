// Scope Portfolio. All rights reserved


#include "SP_LocalPlayerMeshManager.h"

#include "SP_AssetManager.h"
#include "SP_GameInstance.h"
#include "ModularCharacterSystem/SP_MergeStruct.h"
#include "ModularCharacterSystem/SP_MergeUtil.h"

DEFINE_LOG_CATEGORY_STATIC(LogLocalPlayerMeshManager, All, All);

void USP_LocalPlayerMeshManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    DefaultPartAsset = GetDefaultParts();
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

void USP_LocalPlayerMeshManager::AddMergeComponent(UMergeComponent* Component)
{
    MergeComponents.AddUnique(Component);
}

TArray<UMergeComponent*> USP_LocalPlayerMeshManager::GetMergeComponents()
{
    return MergeComponents;
}

void USP_LocalPlayerMeshManager::UpdateMesh(UMergeComponent* MergeComponent)
{
    Meshes.Reset();
    
    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(ModularPartsSlot.Body);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr)
                {
                    SKMesh = USP_AssetManager::GetAsset(Mesh);     
                }
                Meshes.Add(SKMesh);
            }
        }
        if(ModularPartsSlot.BodyShare == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Body);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(ModularPartsSlot.Arm);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr)
                {
                    SKMesh = USP_AssetManager::GetAsset(Mesh);     
                }
                Meshes.Add(SKMesh);
            }
        }
        if(ModularPartsSlot.ArmShare == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Arm);  
            Meshes.Add(SKMesh);
            SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Hand);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(ModularPartsSlot.Leg);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr)
                {
                    SKMesh = USP_AssetManager::GetAsset(Mesh);     
                }
                Meshes.Add(SKMesh);
            }
        }
        if(ModularPartsSlot.LegShare == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Leg);  
            Meshes.Add(SKMesh);
            SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Feet);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(ModularPartsSlot.Suit);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr)
                {
                    SKMesh = USP_AssetManager::GetAsset(Mesh);     
                }
                Meshes.Add(SKMesh);
            }
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(ModularPartsSlot.Head);    
        if(Item == nullptr) return;
        if(Item->Data.Meshes.Num() > 0)
        {
            for (auto Mesh : Item->Data.Meshes)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = Mesh.Get()) == nullptr)
                {
                    SKMesh = USP_AssetManager::GetAsset(Mesh);     
                }
                Meshes.Add(SKMesh);
            }
        }
    }
    
    USkeleton* Skeleton = USP_AssetManager::GetAsset(DefaultPartAsset->Skeleton);
    FSkeletalMeshMergeParamsScope MeshMergeParams;
    MeshMergeParams.Skeleton = Skeleton;
    MeshMergeParams.MeshesToMerge = Meshes;

    if(auto MergedMesh = USP_MergeUtil::MergeMeshes(MeshMergeParams))
    {
        if(ModularPartsSlot.HeadShare == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Head);
            MergeComponent->GetOwnerMesh()->SetSkeletalMesh(SKMesh, false);
            MergeComponent->GetClothMesh()->SetSkeletalMeshAsset(MergedMesh);
            MergeComponent->GetClothMesh()->SetLeaderPoseComponent(MergeComponent->GetOwnerMesh());
            AllUpdateMorphTarget();
        }
        else
        {
            MergeComponent->GetOwnerMesh()->SetSkeletalMeshAsset(MergedMesh);
        }
    }
}

void USP_LocalPlayerMeshManager::FindAndAddMeshItemData(FPrimaryAssetType Type, FName Name)
{
    if(MeshItemData.Find(Type))
    {
        MeshItemData.Remove(Type);
        MeshItemData.Compact();
        MeshItemData.Shrink();
        MeshItemData.Add(Type, Name);
    }
    else
    {
        MeshItemData.Add(Type, Name);
    }
}

void USP_LocalPlayerMeshManager::WearItem(USP_ModularItemBase* Item)
{
        if(Item->Data.ItemType == USP_AssetManager::Module_BodyType)
    {
        ModularPartsSlot.Body = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            if(ModularPartsSlot.BodyShare > 0) ModularPartsSlot.BodyShare--;
        }
        else
        {
            if(Item->Data.OverlapBody)
            {
                ModularPartsSlot.BodyShare++;
                UpdateWidget(USP_AssetManager::Module_SuitType);
            }
            else if(ModularPartsSlot.BodyShare > 0) ModularPartsSlot.BodyShare--;
        }

        return;
    }

    if(Item->Data.ItemType  == USP_AssetManager::Module_HeadType)
    {
        ModularPartsSlot.Head = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            if(ModularPartsSlot.HeadShare > 0) ModularPartsSlot.HeadShare--;
        }
        else
        {
            if(Item->Data.OverlapBody) { ModularPartsSlot.HeadShare++;}
            else if(ModularPartsSlot.HeadShare > 0) ModularPartsSlot.HeadShare--;
        }

        return;
    }
    
    if(Item->Data.ItemType  == USP_AssetManager::Module_FeetAndLegsType)
    {
        ModularPartsSlot.Leg = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            if(ModularPartsSlot.LegShare > 0) ModularPartsSlot.LegShare--;
        }
        else
        {
            if(Item->Data.OverlapBody)
            {
                ModularPartsSlot.LegShare++;
                UpdateWidget(USP_AssetManager::Module_SuitType);
            }
            else if(ModularPartsSlot.LegShare > 0) ModularPartsSlot.LegShare--;
        }

        return;
    }

    if(Item->Data.ItemType  == USP_AssetManager::Module_HandAndArmType)
    {
        ModularPartsSlot.Arm = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            if(ModularPartsSlot.ArmShare > 0) ModularPartsSlot.ArmShare--;
        }
        else
        {
            if(Item->Data.OverlapBody)
            {
                ModularPartsSlot.ArmShare++;
                UpdateWidget(USP_AssetManager::Module_SuitType);
            }
            else if(ModularPartsSlot.ArmShare > 0) ModularPartsSlot.ArmShare--;
        }

        return;
    }

    if(Item->Data.ItemType  == USP_AssetManager::Module_SuitType)
    {
        ModularPartsSlot.Suit = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            if(ModularPartsSlot.BodyShare > 0) ModularPartsSlot.BodyShare--;
            if(ModularPartsSlot.ArmShare > 0) ModularPartsSlot.ArmShare--;
            if(ModularPartsSlot.LegShare > 0) ModularPartsSlot.LegShare--;
        }
        else
        {
            if(Item->Data.OverlapBody)
            {
                ModularPartsSlot.BodyShare++;
                ModularPartsSlot.ArmShare++;
                ModularPartsSlot.LegShare++;
                UpdateWidget(USP_AssetManager::Module_BodyType);
                UpdateWidget(USP_AssetManager::Module_HandAndArmType);
                UpdateWidget(USP_AssetManager::Module_FeetAndLegsType);
            }
            else
            {
                if(ModularPartsSlot.BodyShare > 0) ModularPartsSlot.BodyShare--;
                if(ModularPartsSlot.ArmShare > 0) ModularPartsSlot.ArmShare--;
                if(ModularPartsSlot.LegShare > 0) ModularPartsSlot.LegShare--;
            }
        }
    }
}

void USP_LocalPlayerMeshManager::ReplaceItemInSlot(USP_ModularItemBase* Item)
{
    WearItem(Item);

    if(ModularPartsSlot.Head == nullptr || ModularPartsSlot.Arm == nullptr || ModularPartsSlot.Body == nullptr ||
       ModularPartsSlot.Leg == nullptr || ModularPartsSlot.Suit == nullptr) return;
    
    for(const auto Component : MergeComponents)
    {
        UpdateMesh(Component);
    }
}

void USP_LocalPlayerMeshManager::SetMorphTarget(FString MorphTargetName, float Value)
{
    const FName TargetName = FName(*MorphTargetName);
    for (const auto Component : MergeComponents)
    {
        Component->SetMorphTarget(TargetName, Value, false);
    }
    
    if(MorphTargetData.RemoveAndCopyValue(TargetName, Value))
    {
        MorphTargetData.Compact();
        MorphTargetData.Shrink();
        MorphTargetData.Add(TargetName, Value);
        UE_LOG(LogLocalPlayerMeshManager, Log, TEXT("RemoveAndAdd : %s"), *MorphTargetName);
    }
    else
    {
        MorphTargetData.Add(TargetName, Value);
        UE_LOG(LogLocalPlayerMeshManager, Log, TEXT("Add : %s"), *MorphTargetName);
    }
}

void USP_LocalPlayerMeshManager::AllUpdateMorphTarget()
{
    if(MorphTargetData.Num() == 0) return;
    
    for (const auto Component : MergeComponents)
    {
        Component->ClearMorphTarget();
        for (const auto Data : MorphTargetData)
        {
            Component->SetMorphTarget(Data.Key, Data.Value, false);
        }
    }
}

void USP_LocalPlayerMeshManager::ResetMorphTargetData()
{
    for (const auto Component : MergeComponents)
    {
        for (const auto Data : MorphTargetData)
        {
            Component->ClearMorphTarget();
            Component->SetMorphTarget(Data.Key, 0, false);
            UE_LOG(LogLocalPlayerMeshManager, Log, TEXT("Reset : %s"), *Data.Key.ToString());
        }
    }
    
    MorphTargetData.Empty();
}

FModularPartsSlotData* USP_LocalPlayerMeshManager::GetPartsSlot()
{
    return &ModularPartsSlot;
}

FPlayerMeshData USP_LocalPlayerMeshManager::SaveMeshData() const
{
    FPlayerMeshData Data;
    Data.Meshes = Meshes;
    Data.MorphTargetData = MorphTargetData;
    Data.MeshItemData = MeshItemData;

    return Data;
}
