// Scope Portfolio. All rights reserved


#include "MergeComponent.h"

#include "SP_AssetManager.h"
#include "SP_PlayerCharacter.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"

void UMergeComponent::BeginPlay()
{
    Super::BeginPlay();
    const auto LPM = GetOwner()->GetNetOwningPlayer()->GetPlayerController(GetWorld())->GetLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>();
    LPM->AddMergeComponent(this);
}

USkeletalMeshComponent* UMergeComponent::GetClothMesh() const
{
    const auto Character = Cast<ASP_BaseCharacter>(GetOwner());
    if(Character) return Character->GetClothMesh();
    return nullptr;
}

USkeletalMeshComponent* UMergeComponent::GetOwnerMesh() const
{
    return Cast<ACharacter>(GetOwner())->GetMesh();
}

void UMergeComponent::UpdateMesh(USkeletalMesh* NewMesh) const
{
    GetClothMesh()->SetSkeletalMeshAsset(NewMesh);
}

void UMergeComponent::SetMorphTarget(FName MorphTargetName, float Value, bool RemoveWeight) const
{
    if(const auto MeshComp = GetOwnerMesh())
    {
        MeshComp->SetMorphTarget(MorphTargetName, Value, RemoveWeight);
    }
}

void UMergeComponent::ClearMorphTarget()
{
    if(const auto MeshComp = GetOwnerMesh())
    {
        MeshComp->ClearMorphTargets();
    }
}
