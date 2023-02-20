// Scope Portfolio. All rights reserved


#include "SP_MergeComponent.h"
#include "SP_AssetManager.h"
#include "SP_PlayerCharacter.h"
#include "SP_PlayerState.h"


void USP_MergeComponent::BeginPlay()
{
    Super::BeginPlay();

    // 시스템이 설정하는 NPC의 메시 정보라도 LocalPlayerSubsystem을 통해 메시를 생성합니다.
    GetOwner()->GetNetOwningPlayer()->GetPlayerController(GetWorld())->GetPlayerState<ASP_PlayerState>()->UpdateMergeComponent(this, PawnType);
}

USkeletalMeshComponent* USP_MergeComponent::GetOwnerMesh() const
{
    return Cast<ACharacter>(GetOwner())->GetMesh();
}

EMergePawnType USP_MergeComponent::GetPawnType() const
{
    return PawnType;
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
