// Scope Portfolio. All rights reserved


#include "SP_MergeComponent.h"

#include "SP_AssetManager.h"
#include "SP_PlayerCharacter.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"

void USP_MergeComponent::BeginPlay()
{
    Super::BeginPlay();
    const auto LPM = GetOwner()->GetNetOwningPlayer()->GetPlayerController(GetWorld())->GetLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>();
    LPM->AddMergeComponent(this);
}

USkeletalMeshComponent* USP_MergeComponent::GetClothMesh() const
{
    const auto Character = Cast<ASP_PlayerCharacter>(GetOwner());
    if(Character) return Character->GetClothMesh();
    return nullptr;
}

USkeletalMeshComponent* USP_MergeComponent::GetOwnerMesh() const
{
    return Cast<ACharacter>(GetOwner())->GetMesh();
}

void USP_MergeComponent::UpdateMesh(USkeletalMesh* NewMesh) const
{
    GetClothMesh()->SetSkeletalMeshAsset(NewMesh);
}

void USP_MergeComponent::SetMorphTarget(FName MorphTargetName, float Value, bool RemoveWeight) const
{
    if(const auto MeshComp = GetOwnerMesh()) MeshComp->SetMorphTarget(MorphTargetName, Value, RemoveWeight);
}

void USP_MergeComponent::ClearMorphTarget()
{
    if(const auto MeshComp = GetOwnerMesh()) MeshComp->ClearMorphTargets();
}

void USP_MergeComponent::UpdateAnimation(UAnimationAsset* Asset)
{
    GetOwnerMesh()->SetAnimation(Asset);
    GetOwnerMesh()->Play(true);
}
