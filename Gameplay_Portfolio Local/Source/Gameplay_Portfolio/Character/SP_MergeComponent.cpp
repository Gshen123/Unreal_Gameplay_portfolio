// Scope Portfolio. All rights reserved


#include "SP_MergeComponent.h"

#include "SP_AssetManager.h"
#include "SP_BaseCharacter.h"
#include "SP_GameInstance.h"
#include "SP_PlayerState.h"
#include "GameFramework/Character.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "ModularCharacterSystem/SP_MergeStruct.h"
#include "ModularCharacterSystem/SP_MergeUtil.h"


// Sets default values for this component's properties
USP_MergeComponent::USP_MergeComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
    // ...
}


// Called when the game starts
void USP_MergeComponent::BeginPlay()
{
    Super::BeginPlay();

    
    DefaultPartAsset = GetDefaultParts();
    UpdateMesh();
}

void USP_MergeComponent::UpdateMesh()
{
    Meshes.Reset();
    const FModularPartsSlotData& PartsAsset= GetPlayerState()->GetPartsData();
    
    if(PartsAsset.Head != nullptr)
    {
        USP_ModularItemBase* Item;
        if((Item = PartsAsset.Head.Get()) == nullptr)
        {
            Item = USP_AssetManager::GetAsset(PartsAsset.Head);       
        }

        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            Unwear(Item->Data.WearStatus);
        }
        else
        {
            if(CheckWearStatus(Item->Data.WearStatus))
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

                if(Item->Data.OverlapBody)
                {
                    ModularPartsSlot.HeadShare++;
                }
            }
        }

        if(ModularPartsSlot.HeadShare == 0)
        {
            USkeletalMesh* SKMesh;
            if((SKMesh = DefaultPartAsset->DefaultParts.Head.Get()) == nullptr)
            {
                SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->DefaultParts.Head);     
            }
            Meshes.Add(SKMesh);
        }
    }

    if(PartsAsset.Top != nullptr)
    {
        USP_ModularItemBase* Item;
        if((Item = PartsAsset.Top.Get()) == nullptr)
        {
            Item = USP_AssetManager::GetAsset(PartsAsset.Top);       
        }

        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            Unwear(Item->Data.WearStatus);
        }
        else
        {
            if(CheckWearStatus(Item->Data.WearStatus))
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

                if(Item->Data.OverlapBody)
                {
                    ModularPartsSlot.BodyShare++;
                    ModularPartsSlot.BodyCount--;
                }
            }
        }

        if(ModularPartsSlot.BodyShare == 0)
        {
            if(ModularPartsSlot.BodyCount == 0)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = DefaultPartAsset->DefaultParts.Body.Get()) == nullptr)
                {
                    SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->DefaultParts.Body);     
                }
                Meshes.Add(SKMesh);
                ModularPartsSlot.BodyCount++;
            }
        }
    }

    if(PartsAsset.Bottom != nullptr)
    {
        USP_ModularItemBase* Item;
        if((Item = PartsAsset.Bottom.Get()) == nullptr)
        {
            Item = USP_AssetManager::GetAsset(PartsAsset.Bottom);       
        }

        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            Unwear(Item->Data.WearStatus);
        }
        else
        {
            if(CheckWearStatus(Item->Data.WearStatus))
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

                if(Item->Data.OverlapBody)
                {
                    ModularPartsSlot.BodyShare++;
                    ModularPartsSlot.BodyCount--;
                }
            }
        }

        if(ModularPartsSlot.BodyShare == 0)
        {
            if(ModularPartsSlot.BodyCount == 0)
            {
                USkeletalMesh* SKMesh;
                if((SKMesh = DefaultPartAsset->DefaultParts.Body.Get()) == nullptr)
                {
                    SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->DefaultParts.Body);     
                }
                Meshes.Add(SKMesh);
                ModularPartsSlot.BodyCount++;
            }
        }
    }

    if(PartsAsset.Arm != nullptr)
    {
        USP_ModularItemBase* Item;
        if((Item = PartsAsset.Arm.Get()) == nullptr)
        {
            Item = USP_AssetManager::GetAsset(PartsAsset.Arm);       
        }

        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            Unwear(Item->Data.WearStatus);
        }
        else
        {
            if(CheckWearStatus(Item->Data.WearStatus))
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

                if(Item->Data.OverlapBody)
                {
                    ModularPartsSlot.ArmShare++;
                }
            }
        }

        if(ModularPartsSlot.ArmShare == 0)
        {
            USkeletalMesh* SKMesh;
            if((SKMesh = DefaultPartAsset->DefaultParts.Arm.Get()) == nullptr)
            {
                SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->DefaultParts.Arm);     
            }
            Meshes.Add(SKMesh);
            
            if((SKMesh = DefaultPartAsset->DefaultParts.Hand.Get()) == nullptr)
            {
                SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->DefaultParts.Hand);     
            }
            Meshes.Add(SKMesh);
        }
    }

    if(PartsAsset.Leg != nullptr)
    {
        USP_ModularItemBase* Item;
        if((Item = PartsAsset.Leg.Get()) == nullptr)
        {
            Item = USP_AssetManager::GetAsset(PartsAsset.Leg);       
        }

        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            Unwear(Item->Data.WearStatus);
        }
        else
        {
            if(CheckWearStatus(Item->Data.WearStatus))
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

                if(Item->Data.OverlapBody)
                {
                    ModularPartsSlot.LegShare++;
                }
            }
        }

        if(ModularPartsSlot.LegShare == 0)
        {
            USkeletalMesh* SKMesh;
            if((SKMesh = DefaultPartAsset->DefaultParts.Leg.Get()) == nullptr)
            {
                SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->DefaultParts.Leg);     
            }
            Meshes.Add(SKMesh);
            if((SKMesh = DefaultPartAsset->DefaultParts.Feet.Get()) == nullptr)
            {
                SKMesh = USP_AssetManager::GetAsset(DefaultPartAsset->DefaultParts.Feet);     
            }
            Meshes.Add(SKMesh);
        }
    }

    if(PartsAsset.Suit != nullptr)
    {
        USP_ModularItemBase* Item;
        if((Item = PartsAsset.Suit.Get()) == nullptr)
        {
            Item = USP_AssetManager::GetAsset(PartsAsset.Suit);       
        }

        if(Item->Data.DisplayName.EqualTo(FText::FromString("None")))
        {
            Unwear(Item->Data.WearStatus);
        }
        else
        {
            if(CheckWearStatus(Item->Data.WearStatus))
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

                if(Item->Data.OverlapBody)
                {
                    ModularPartsSlot.ArmShare++;
                    ModularPartsSlot.LegShare++;
                    ModularPartsSlot.BodyShare++;
                    ModularPartsSlot.BodyCount--;
                }
            }
        }
    }

    FSkeletalMeshMergeParamsScope MeshMergeParams;

    USkeleton* Skeleton;
    if((Skeleton = DefaultPartAsset->DefaultParts.Skeleton.Get()) == nullptr)
    {
        Skeleton = USP_AssetManager::GetAsset(DefaultPartAsset->DefaultParts.Skeleton);
    }
    
    MeshMergeParams.Skeleton = Skeleton;
    MeshMergeParams.MeshesToMerge = Meshes;
    ASP_BaseCharacter* Character = Cast<ASP_BaseCharacter>(GetOwner());

    if(auto MergedMesh = USP_MergeUtil::MergeMeshes(MeshMergeParams))
    {
        Character->GetMesh()->SetSkeletalMeshAsset(MergedMesh);
    }
}

ASP_PlayerState* USP_MergeComponent::GetPlayerState() const
{
    const auto Chr= Cast<ACharacter>(GetOwner());
    if(!Chr) return nullptr;

    const auto PS= Cast<ASP_PlayerState>(Chr->GetPlayerState());
    if(!PS) return nullptr;

    return PS;
}


USP_DefaultPartsAsset* USP_MergeComponent::GetDefaultParts() const
{
    auto GameInstance = Cast<USP_GameInstance>(GetOwner()->GetGameInstance());
    if(!GameInstance) return nullptr;

    return GameInstance->GetDefaultMeshParts();
}

bool USP_MergeComponent::CheckWearStatus(int32 bitmask)
{
    if(WearStatus & bitmask)
    {
        return false;
    }
    
    WearStatus |= bitmask;
    return true;
}

void USP_MergeComponent::Unwear(int32 bitmask)
{
    WearStatus &= ~bitmask;
    
    if(static_cast<int32>(EWearStatus::hasHead) == bitmask)
    {
        ModularPartsSlot.Head = nullptr;
        if(ModularPartsSlot.HeadShare > 0) ModularPartsSlot.HeadShare--;
    }

    if(static_cast<int32>(EWearStatus::hasHandAndArm) == bitmask)
    {
        ModularPartsSlot.Arm = nullptr;
        if(ModularPartsSlot.ArmShare > 0) ModularPartsSlot.ArmShare--;
    }
    
    if(static_cast<int32>(EWearStatus::hasFeetAndLeg) == bitmask)
    {
        ModularPartsSlot.Leg = nullptr;
        if(ModularPartsSlot.LegShare > 0) ModularPartsSlot.LegShare--;
    }

    if(static_cast<int32>(EWearStatus::hasTop) == bitmask)
    {
        ModularPartsSlot.Top = nullptr;
        if(ModularPartsSlot.BodyShare > 0) ModularPartsSlot.BodyShare--;
    }

    if(static_cast<int32>(EWearStatus::hasBottom) == bitmask)
    {
        ModularPartsSlot.Bottom = nullptr;
        if(ModularPartsSlot.BodyShare > 0) ModularPartsSlot.BodyShare--;
    }

    if((static_cast<int32>(EWearStatus::hasBottom) & static_cast<int32>(EWearStatus::hasTop)
        & static_cast<int32>(EWearStatus::hasHandAndArm) & static_cast<int32>(EWearStatus::hasFeetAndLeg)) == bitmask)
    {
        ModularPartsSlot.Suit = nullptr;
        if(ModularPartsSlot.BodyShare > 0) ModularPartsSlot.BodyShare--;
        if(ModularPartsSlot.ArmShare > 0) ModularPartsSlot.ArmShare--;
        if(ModularPartsSlot.LegShare > 0) ModularPartsSlot.LegShare--;
    }
}

