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
    MergeComponents.Reset();
    Super::Deinitialize();
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
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(ModularPartsSlot.Body);    
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
        if(ModularPartsSlot.BodyShare.Num() == 0)
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
                if((SKMesh = Mesh.Get()) == nullptr) SKMesh = USP_AssetManager::GetAsset(Mesh);     
                Meshes.Add(SKMesh);
            }
        }
        if(ModularPartsSlot.ArmShare.Num() == 0)
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
                if((SKMesh = Mesh.Get()) == nullptr) SKMesh = USP_AssetManager::GetAsset(Mesh);     
                Meshes.Add(SKMesh);
            }
        }
        if(ModularPartsSlot.LegShare.Num() == 0)
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
                if((SKMesh = Mesh.Get()) == nullptr) SKMesh = USP_AssetManager::GetAsset(Mesh);     
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
        if(ModularPartsSlot.HeadShare.Num() == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Head);
            MergeComponent->GetOwnerMesh()->SetSkeletalMesh(SKMesh, false);

            if(MergedMesh != nullptr) MergeComponent->GetClothMesh()->SetSkeletalMeshAsset(MergedMesh);
            else MergeComponent->GetClothMesh()->SetSkeletalMeshAsset(Meshes[0]);
            
            MergeComponent->GetClothMesh()->SetLeaderPoseComponent(MergeComponent->GetOwnerMesh());
            AllUpdateMorphTarget();
            UpdateMaterial(MergeComponent);
        }
        else
        {
            if(MergedMesh != nullptr) MergeComponent->GetOwnerMesh()->SetSkeletalMeshAsset(MergedMesh);
            else MergeComponent->GetOwnerMesh()->SetSkeletalMeshAsset(Meshes[0]);
            MergeComponent->GetClothMesh()->SetSkeletalMeshAsset(nullptr);
        }
    }
}

void USP_LocalPlayerMeshManager::AllUpdateMaterail()
{
    for (const auto MergeComponent : MergeComponents)
    {
        UpdateMaterial(MergeComponent);
    }
}

void USP_LocalPlayerMeshManager::UpdateMaterial(USP_MergeComponent* MergeComponent)
{
    for (auto iter = MaterialData.CreateConstIterator(); iter; ++iter)
    {
        FMaterialData* Data = MaterialData.Find(iter.Key());
        UMaterialInstanceDynamic* HeadDynamicMesh =  MergeComponent->GetOwnerMesh()->CreateDynamicMaterialInstance(iter.Key(), Data->MaterialInstance);
        for (auto it= Data->ParamData.CreateConstIterator(); it; ++it)
        {
            HeadDynamicMesh->SetVectorParameterValue(it.Key(), it.Value());
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
    else MeshItemData.Add(Type, Name);
}

void USP_LocalPlayerMeshManager::FindAndAddMaterialData(int32 Index, FName ParamName, FLinearColor Value, UMaterialInstance* MaterialInstance)
{
    if(const auto PrevData = MaterialData.Find(Index))
    {
        PrevData->ParamData.Add(ParamName, Value);
    }
    else
    {
        FMaterialData NewData;
        NewData.MaterialInstance = MaterialInstance;
        NewData.ParamData.Add(ParamName, Value);
        MaterialData.Add(Index, NewData);
    }
}

void USP_LocalPlayerMeshManager::WearItem(USP_ModularItemBase* Item)
{
    if(Item->Data.ItemType == USP_AssetManager::Module_BodyType)
    {
        ModularPartsSlot.Body = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(ModularPartsSlot.BodyShare.Num() > 0)
            {
                if(ModularPartsSlot.BodyShare.Contains(USP_AssetManager::Module_BodyType)) ModularPartsSlot.BodyShare.Remove(USP_AssetManager::Module_BodyType);
            }
        }
        else
        {
            ModularPartsSlot.BodyShare.AddUnique(USP_AssetManager::Module_BodyType);
            UpdateWidget(USP_AssetManager::Module_SuitType);
        }
        return;
    }

    if(Item->Data.ItemType  == USP_AssetManager::Module_HeadType)
    {
        ModularPartsSlot.Head = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(ModularPartsSlot.HeadShare.Num() > 0)
            {
                if(ModularPartsSlot.HeadShare.Contains(USP_AssetManager::Module_HeadType)) ModularPartsSlot.HeadShare.Remove(USP_AssetManager::Module_HeadType);
            }
        }
        else
        {
            ModularPartsSlot.HeadShare.AddUnique(USP_AssetManager::Module_HeadType);
        }
        return;
    }
    
    if(Item->Data.ItemType  == USP_AssetManager::Module_FeetAndLegsType)
    {
        ModularPartsSlot.Leg = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(ModularPartsSlot.LegShare.Num() > 0)
            {
                if(ModularPartsSlot.LegShare.Contains(USP_AssetManager::Module_FeetAndLegsType)) ModularPartsSlot.LegShare.Remove(USP_AssetManager::Module_FeetAndLegsType);
            }
        }
        else
        {
            ModularPartsSlot.LegShare.AddUnique(USP_AssetManager::Module_FeetAndLegsType);
        }
        return;
    }

    if(Item->Data.ItemType  == USP_AssetManager::Module_HandAndArmType)
    {
        ModularPartsSlot.Arm = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(ModularPartsSlot.ArmShare.Num() > 0)
            {
                if(ModularPartsSlot.ArmShare.Contains(USP_AssetManager::Module_HandAndArmType)) ModularPartsSlot.ArmShare.Remove(USP_AssetManager::Module_HandAndArmType);
            }
        }
        else
        {
            ModularPartsSlot.ArmShare.AddUnique(USP_AssetManager::Module_HandAndArmType);
            UpdateWidget(USP_AssetManager::Module_SuitType);
        }
        return;
    }

    if(Item->Data.ItemType  == USP_AssetManager::Module_SuitType)
    {
        ModularPartsSlot.Suit = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(ModularPartsSlot.BodyShare.Num() > 0)
                if(ModularPartsSlot.BodyShare.Contains(USP_AssetManager::Module_SuitType))
                    ModularPartsSlot.BodyShare.Remove(USP_AssetManager::Module_SuitType);
            
            if(ModularPartsSlot.ArmShare.Num() > 0)
                if(ModularPartsSlot.ArmShare.Contains(USP_AssetManager::Module_SuitType))
                    ModularPartsSlot.ArmShare.Remove(USP_AssetManager::Module_SuitType);
        }
        else
        {
            ModularPartsSlot.BodyShare.AddUnique(USP_AssetManager::Module_SuitType);
            ModularPartsSlot.ArmShare.AddUnique(USP_AssetManager::Module_SuitType);
            UpdateWidget(USP_AssetManager::Module_BodyType);
            UpdateWidget(USP_AssetManager::Module_HandAndArmType);
        }
    }
}

void USP_LocalPlayerMeshManager::ReplaceItemInSlot(USP_ModularItemBase* Item)
{
    WearItem(Item);

    if(ModularPartsSlot.Head == nullptr || ModularPartsSlot.Arm == nullptr || ModularPartsSlot.Body == nullptr ||
       ModularPartsSlot.Leg == nullptr || ModularPartsSlot.Suit == nullptr) return;
    
    for(const auto Component : MergeComponents) UpdateMesh(Component);
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

void USP_LocalPlayerMeshManager::UpdateAnimation(UAnimationAsset* Asset)
{
    for (const auto Component : MergeComponents) Component->UpdateAnimation(Asset);
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
