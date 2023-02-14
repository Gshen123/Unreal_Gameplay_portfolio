// Scope Portfolio. All rights reserved


#include "SP_MergeComponent.h"

#include "SP_AssetManager.h"
#include "SP_PlayerCharacter.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"


void USP_MergeComponent::BeginPlay()
{
    Super::BeginPlay();
    
    const auto LocalPlayerMeshManager = GetOwner()->GetNetOwningPlayer()->GetPlayerController(GetWorld())->GetLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>();
    LocalPlayerMeshManager->AddMergeComponent(this);
}

USkeletalMeshComponent* USP_MergeComponent::GetOwnerMesh() const
{
    return Cast<ACharacter>(GetOwner())->GetMesh();
}

void USP_MergeComponent::SetOwnerMorphTarget(FName MorphTargetName, float Value, bool RemoveWeight) const
{
    if(const auto MeshComp = GetOwnerMesh()) MeshComp->SetMorphTarget(MorphTargetName, Value, RemoveWeight);
}

void USP_MergeComponent::ClearMorphTarget() const
{
    if(const auto MeshComp = GetOwnerMesh()) MeshComp->ClearMorphTargets();
}

void USP_MergeComponent::UpdateAnimation(UAnimationAsset* Asset) const
{
    if(!Asset) { GetOwnerMesh()->Stop(); return;}
    
    GetOwnerMesh()->SetAnimation(Asset);
    GetOwnerMesh()->Play(true);
}
