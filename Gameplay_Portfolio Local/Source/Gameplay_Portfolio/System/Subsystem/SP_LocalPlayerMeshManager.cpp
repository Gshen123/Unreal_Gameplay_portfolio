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
    PlayerMeshData.Empty();
    NPCMeshData.Empty();
    MergeComponents.Empty();
    bIsInit = false;
    Super::Deinitialize();
}

void USP_LocalPlayerMeshManager::MeshDataInit(FSaveMeshData LoadPlayerMeshData, TMap<EMergePawnType, FSaveMeshData> LoadNPCMeshData)
{
    PlayerMeshData = LoadPlayerMeshData;
    NPCMeshData = LoadNPCMeshData;
    bIsInit = true;
}

FSaveMeshData USP_LocalPlayerMeshManager::GetMeshData(EMergePawnType PawnType)
{
    if(PawnType >= EMergePawnType::NPC1) return *NPCMeshData.Find(PawnType);
    return PlayerMeshData;
}

bool USP_LocalPlayerMeshManager::IsInit() const
{
    return bIsInit;
}

void USP_LocalPlayerMeshManager::UpdateWidget(FPrimaryAssetType Type) const
{
    WidgetUpdated.Broadcast(Type);
}

USP_DefaultPartsAsset* USP_LocalPlayerMeshManager::GetDefaultParts() const
{
    const auto GI = GetWorld()->GetGameInstance<USP_GameInstance>();
    check(GI != nullptr);
    return GI->GetDefaultMeshParts();
}

void USP_LocalPlayerMeshManager::AddMergeComponent(USP_MergeComponent* Component, EMergePawnType PawnType)
{
    MergeComponents.Add(PawnType, Component);
    
    TArray<USP_MergeComponent*> FindComponents;
    MergeComponents.MultiFind(PawnType, FindComponents);

    if(FindComponents.IsEmpty()) return;
    if(PawnType >= EMergePawnType::NPC1 && NPCMeshData.IsEmpty()) return;
    
    for (const auto FindComponent : FindComponents)
    {
        UpdateMesh(FindComponent);
        UpdateMaterial(FindComponent);
        LoadMorphTarget(FindComponent->GetPawnType());
    }
}

TArray<USP_MergeComponent*> USP_LocalPlayerMeshManager::FindMergeComponent(EMergePawnType Key) const
{
    TArray<USP_MergeComponent*> FindComponents;
    MergeComponents.MultiFind(Key, FindComponents);
    return FindComponents;
}

void USP_LocalPlayerMeshManager::UpdateMesh(USP_MergeComponent* MergeComponent)
{
    auto MeshData = MergeComponent->GetPawnType() >= EMergePawnType::NPC1 ? NPCMeshData.Find(MergeComponent->GetPawnType()) : &PlayerMeshData;
    Meshes.Reset();
    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData->ModularPartsSlot.Body);    
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
        if(MeshData->ModularPartsSlot.BodyShare.Num() == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Body);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData->ModularPartsSlot.Arm);    
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
        if(MeshData->ModularPartsSlot.ArmShare.Num() == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Arm);  
            Meshes.Add(SKMesh);
            SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Hand);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData->ModularPartsSlot.Leg);    
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
        if(MeshData->ModularPartsSlot.LegShare.Num() == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Leg);  
            Meshes.Add(SKMesh);
            SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Feet);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData->ModularPartsSlot.Suit);    
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
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(MeshData->ModularPartsSlot.Head);    
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
        if(MeshData->ModularPartsSlot.HeadShare.Num() == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Head);
            MergeComponent->GetOwnerMesh()->SetSkeletalMesh(SKMesh, false);

            if(MergedMesh != nullptr) MergeComponent->SetSkeletalMeshAsset(MergedMesh);
            else MergeComponent->SetSkeletalMeshAsset(Meshes[0]);
            
            MergeComponent->SetLeaderPoseComponent(MergeComponent->GetOwnerMesh());
            LoadMorphTarget(MergeComponent->GetPawnType());
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

void USP_LocalPlayerMeshManager::WearItem(const USP_ModularItemBase* Item, EMergePawnType PawnType, FName DefaultItemName)
{
    const auto MeshData = PawnType >= EMergePawnType::NPC1 ? NPCMeshData.Find(PawnType) : &PlayerMeshData;
    
    if(Item->Data.ItemType == USP_AssetManager::Module_BodyType)
    {
        MeshData->ModularPartsSlot.Body = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData->ModularPartsSlot.BodyShare.Num() > 0)
                if(MeshData->ModularPartsSlot.BodyShare.Contains(USP_AssetManager::Module_BodyType))
                    MeshData->ModularPartsSlot.BodyShare.Remove(USP_AssetManager::Module_BodyType);
        }
        else MeshData->ModularPartsSlot.BodyShare.AddUnique(USP_AssetManager::Module_BodyType);
        if(!Item->Data.DisplayName.EqualTo(FText::FromName(DefaultItemName))) UpdateWidget(USP_AssetManager::Module_SuitType);
        return;
    }

    if(Item->Data.ItemType == USP_AssetManager::Module_HeadType)
    {
        MeshData->ModularPartsSlot.Head = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData->ModularPartsSlot.HeadShare.Num() > 0)
                if(MeshData->ModularPartsSlot.HeadShare.Contains(USP_AssetManager::Module_HeadType))
                    MeshData->ModularPartsSlot.HeadShare.Remove(USP_AssetManager::Module_HeadType);
        }
        else MeshData->ModularPartsSlot.HeadShare.AddUnique(USP_AssetManager::Module_HeadType);
        return;
    }
    
    if(Item->Data.ItemType == USP_AssetManager::Module_FeetAndLegsType)
    {
        MeshData->ModularPartsSlot.Leg = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData->ModularPartsSlot.LegShare.Num() > 0)
                if(MeshData->ModularPartsSlot.LegShare.Contains(USP_AssetManager::Module_FeetAndLegsType))
                    MeshData->ModularPartsSlot.LegShare.Remove(USP_AssetManager::Module_FeetAndLegsType);
        }
        else MeshData->ModularPartsSlot.LegShare.AddUnique(USP_AssetManager::Module_FeetAndLegsType);
        if(!Item->Data.DisplayName.EqualTo(FText::FromName(DefaultItemName))) UpdateWidget(USP_AssetManager::Module_SuitType);
        return;
    }

    if(Item->Data.ItemType == USP_AssetManager::Module_HandAndArmType)
    {
        MeshData->ModularPartsSlot.Arm = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData->ModularPartsSlot.ArmShare.Num() > 0)
                if(MeshData->ModularPartsSlot.ArmShare.Contains(USP_AssetManager::Module_HandAndArmType))
                    MeshData->ModularPartsSlot.ArmShare.Remove(USP_AssetManager::Module_HandAndArmType);
        }
        else MeshData->ModularPartsSlot.ArmShare.AddUnique(USP_AssetManager::Module_HandAndArmType);
        if(!Item->Data.DisplayName.EqualTo(FText::FromName(DefaultItemName))) UpdateWidget(USP_AssetManager::Module_SuitType);
        return;
    }

    if(Item->Data.ItemType == USP_AssetManager::Module_SuitType)
    {
        MeshData->ModularPartsSlot.Suit = Item;
        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")) || !Item->Data.OverlapBody)
        {
            if(MeshData->ModularPartsSlot.BodyShare.Num() > 0)
                if(MeshData->ModularPartsSlot.BodyShare.Contains(USP_AssetManager::Module_SuitType))
                    MeshData->ModularPartsSlot.BodyShare.Remove(USP_AssetManager::Module_SuitType);
            if(MeshData->ModularPartsSlot.ArmShare.Num() > 0)
                if(MeshData->ModularPartsSlot.ArmShare.Contains(USP_AssetManager::Module_SuitType))
                    MeshData->ModularPartsSlot.ArmShare.Remove(USP_AssetManager::Module_SuitType);
            if(MeshData->ModularPartsSlot.LegShare.Num() > 0)
                if(MeshData->ModularPartsSlot.LegShare.Contains(USP_AssetManager::Module_SuitType))
                    MeshData->ModularPartsSlot.LegShare.Remove(USP_AssetManager::Module_SuitType);
        }
        else
        {
            MeshData->ModularPartsSlot.BodyShare.AddUnique(USP_AssetManager::Module_SuitType);
            MeshData->ModularPartsSlot.ArmShare.AddUnique(USP_AssetManager::Module_SuitType);
            MeshData->ModularPartsSlot.LegShare.AddUnique(USP_AssetManager::Module_SuitType);
            UpdateWidget(USP_AssetManager::Module_BodyType);
            UpdateWidget(USP_AssetManager::Module_HandAndArmType);
            UpdateWidget(USP_AssetManager::Module_FeetAndLegsType);
        }
    }
}

void USP_LocalPlayerMeshManager::ReplaceItemInSlot(const USP_ModularItemBase* Item, EMergePawnType PawnType, FName DefaultItemName)
{
    const auto MeshData = PawnType >= EMergePawnType::NPC1 ? NPCMeshData.Find(PawnType) : &PlayerMeshData;
    WearItem(Item, PawnType, DefaultItemName);

    if(MeshData->ModularPartsSlot.Head == nullptr || MeshData->ModularPartsSlot.Arm == nullptr || MeshData->ModularPartsSlot.Body == nullptr ||
       MeshData->ModularPartsSlot.Leg == nullptr || MeshData->ModularPartsSlot.Suit == nullptr) return;
    
    for(const auto FindComponent : FindMergeComponent(PawnType)) UpdateMesh(FindComponent);
}

void USP_LocalPlayerMeshManager::FindAndAddMeshItemData(FPrimaryAssetType Type, FString Name, EMergePawnType PawnType)
{
    const auto MeshData = PawnType >= EMergePawnType::NPC1 ? NPCMeshData.Find(PawnType) : &PlayerMeshData;
    
    if(MeshData->MeshItemData.Find(Type))
    {
        MeshData->MeshItemData.Remove(Type);
        MeshData->MeshItemData.Compact();
        MeshData->MeshItemData.Shrink();
        MeshData->MeshItemData.Add(Type, Name);
    }
    else MeshData->MeshItemData.Add(Type, Name);
}

void USP_LocalPlayerMeshManager::AllUpdateMaterial(EMergePawnType PawnType)
{
    for (const auto Component : FindMergeComponent(PawnType)) UpdateMaterial(Component);
}

void USP_LocalPlayerMeshManager::UpdateMaterial(const USP_MergeComponent* MergeComponent)
{
    const auto MeshData = MergeComponent->GetPawnType() >= EMergePawnType::NPC1 ? NPCMeshData.Find(MergeComponent->GetPawnType()) : &PlayerMeshData;
    
    for (auto iter = MeshData->MaterialData.CreateConstIterator(); iter; ++iter)
    {
        const FMaterialData* Data = MeshData->MaterialData.Find(iter.Key());
        UMaterialInstanceDynamic* HeadDynamicMesh =  MergeComponent->GetOwnerMesh()->CreateDynamicMaterialInstance(iter.Key(), Data->MaterialInstance);

        for (auto it= Data->ParamData.CreateConstIterator(); it; ++it)
            HeadDynamicMesh->SetVectorParameterValue(it.Key(), it.Value());
    }
}

void USP_LocalPlayerMeshManager::FindAndAddMaterialData(int32 Index, FName ParamName, FLinearColor Value, UMaterialInstance* MaterialInstance, EMergePawnType PawnType)
{
    const auto MeshData = PawnType >= EMergePawnType::NPC1 ? NPCMeshData.Find(PawnType) : &PlayerMeshData;
    
    if(const auto PrevData = MeshData->MaterialData.Find(Index))
    {
        PrevData->ParamData.Remove(ParamName);
        PrevData->ParamData.Compact();
        PrevData->ParamData.Shrink();
        PrevData->ParamData.Add(ParamName, Value);
    }
    else MeshData->AddMaterialData(Index, ParamName, Value, MaterialInstance);
}

void USP_LocalPlayerMeshManager::FindAndAddMorphTarget(FString MorphTargetName, float Value, EMergePawnType PawnType)
{
    const FName TargetName = FName(*MorphTargetName);
    const auto MeshData = PawnType >= EMergePawnType::NPC1 ? NPCMeshData.Find(PawnType) : &PlayerMeshData;

    for (const auto Component : FindMergeComponent(PawnType))
        Component->SetOwnerMorphTarget(TargetName, Value, false);
    
    if (MeshData->MorphTargetData.Find(TargetName))
    {
        MeshData->MorphTargetData.Remove(TargetName);
        MeshData->MorphTargetData.Compact();
        MeshData->MorphTargetData.Shrink();
    }
    MeshData->MorphTargetData.Add(TargetName, Value);
}

void USP_LocalPlayerMeshManager::UpdateMorphTarget(const USP_MergeComponent* Component, EMergePawnType PawnType, bool Reset)
{
    Component->ClearMorphTarget();

    const auto MeshData = PawnType >= EMergePawnType::NPC1 ? NPCMeshData.Find(PawnType) : &PlayerMeshData;
    for (const auto Data : MeshData->MorphTargetData)
    {
        if(Reset) Component->SetOwnerMorphTarget(Data.Key, 0.5f, false);
        else Component->SetOwnerMorphTarget(Data.Key, Data.Value, false); 
    }

    if(Reset) MeshData->MorphTargetData.Empty();
}

void USP_LocalPlayerMeshManager::LoadMorphTarget(EMergePawnType PawnType, bool Reset)
{
    const auto MeshData = PawnType >= EMergePawnType::NPC1 ? NPCMeshData.Find(PawnType) : &PlayerMeshData;
    if(MeshData->MorphTargetData.Num() == 0) return;
    
    for (const auto Component : FindMergeComponent(PawnType))
        UpdateMorphTarget(Component, PawnType, Reset);
}

void USP_LocalPlayerMeshManager::UpdateAnimation(UAnimationAsset* Asset, EMergePawnType PawnType) const
{
    for (const auto Component : FindMergeComponent(PawnType)) Component->UpdateAnimation(Asset);
}

FSaveMeshData* USP_LocalPlayerMeshManager::GetPlayerMeshData()
{
    return &PlayerMeshData;
}