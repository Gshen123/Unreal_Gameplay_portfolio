// Scope Portfolio. All rights reserved


#include "SP_PlayerState.h"

#include "SP_AssetManager.h"
#include "SP_PlayerCharacter.h"
#include "SP_GameInstance.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "ModularCharacterSystem/SP_MergeStruct.h"
#include "ModularCharacterSystem/SP_MergeUtil.h"
#include "Subsystem/SP_WorldSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All);

int32 ASP_PlayerState::GetKillsNum() const
{
    return KillCount;
}

int32 ASP_PlayerState::GetCoinsNum() const
{
    return CoinCount;
}

int32 ASP_PlayerState::GetLevelNum() const
{
    return LevelCount;
}

void ASP_PlayerState::SavePlayerState(USP_SaveGame* SaveObject) const
{
    if (SaveObject)
    {
        FPlayerSaveData SaveData;
        // 플레이어의 저장 정보를 업데이트합니다
        // coin = saveobject.coin;
        
        SaveData.PlayerID = GetUniqueId().ToString();
        
        if (APawn* MyPawn = GetPawn())
        {
            SaveData.Location = MyPawn->GetActorLocation();
            SaveData.Rotation = MyPawn->GetActorRotation();
            SaveData.bResumeAtTransform = true;
        }
		
        SaveObject->PlayerSaveDatas.Add(SaveData);
    }
}

void ASP_PlayerState::LoadPlayerState(USP_SaveGame* SaveObject)
{
    if (SaveObject)
    {
        FPlayerSaveData* FoundData = SaveObject->GetPlayerData(this);
        if (FoundData)
        {
            //플레이어 스테이트 정보 갱신
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Could not find SaveGame data for player id '%i'."), GetPlayerId());
        }
    }
}

USkeletalMesh* ASP_PlayerState::UpdateMesh()
{
    UE_LOG(LogPlayerState, Log, TEXT("UpdateMesh"));
    Meshes.Reset();
    DefaultPartAsset = GetDefaultParts();
    
    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(ModularPartsSlot.Head);    
        if(Item == nullptr) return nullptr;
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
        if(ModularPartsSlot.HeadShare == 0)
        {
            USkeletalMesh* SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->Head);  
            Meshes.Add(SKMesh);
        }
    }

    {
        USP_ModularItemBase* Item = USP_AssetManager::GetAsset(ModularPartsSlot.Body);    
        if(Item == nullptr) return nullptr;
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
        if(Item == nullptr) return nullptr;
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
        if(Item == nullptr) return nullptr;
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
        if(Item == nullptr) return nullptr;
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
        return MergedMesh;
    }

    return nullptr;

}

void ASP_PlayerState::ReplaceItemInSlot(USP_ModularItemBase* Item)
{
    WearItem(Item);

    if(ModularPartsSlot.Head == nullptr || ModularPartsSlot.Arm == nullptr || ModularPartsSlot.Body == nullptr ||
       ModularPartsSlot.Leg == nullptr || ModularPartsSlot.Suit == nullptr) return;
    
    auto SK = UpdateMesh();
    if(SK == nullptr) return;

    auto WS = GetWorld()->GetSubsystem<USP_WorldSubsystem>();
    if(WS == nullptr) return;

    auto MergeComponents = WS->GetMergeComponents();
    for(auto Component : MergeComponents)
    {
        Component->UpdateMesh(SK);
    }
}

FModularPartsSlotData* ASP_PlayerState::GetPartsSlot()
{
    return &ModularPartsSlot;
}

USP_DefaultPartsAsset* ASP_PlayerState::GetDefaultParts() const
{
    auto GI = GetGameInstance<USP_GameInstance>();
    check(GI != nullptr);
    return GI->GetDefaultMeshParts();
}

void ASP_PlayerState::WearItem(USP_ModularItemBase* Item)
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
            if(Item->Data.OverlapBody) { ModularPartsSlot.BodyShare++;}
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
            if(Item->Data.OverlapBody) { ModularPartsSlot.LegShare++;}
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
            if(Item->Data.OverlapBody) { ModularPartsSlot.ArmShare++;}
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

void ASP_PlayerState::UpdateWidget(FPrimaryAssetType Type) const
{
    WidgetUpdated.Broadcast(Type);
}
