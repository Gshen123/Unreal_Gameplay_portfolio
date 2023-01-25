// Scope Portfolio. All rights reserved


#include "MergeComponent.h"

#include "SP_BaseCharacter.h"
#include "Subsystem/SP_WorldSubsystem.h"

void UMergeComponent::BeginPlay()
{
    Super::BeginPlay();
    auto WS = GetOwner()->GetGameInstance()->GetSubsystem<USP_WorldSubsystem>();
    WS->AddMergeComponent(this);
}

void UMergeComponent::UpdateMesh(USkeletalMesh* NewMesh)
{
    if(auto Chr = Cast<ASP_BaseCharacter>(GetOwner()))
    {
        Chr->GetMesh()->SetSkeletalMeshAsset(NewMesh);
    }
    else if(auto Pawn = Cast<APawn>(GetOwner()))
    {
        auto Comp = Pawn->GetComponentByClass(USkeletalMeshComponent::StaticClass());
        auto Mesh = Cast<USkeletalMeshComponent>(Comp);
        Mesh->SetSkeletalMeshAsset(NewMesh);
    }
}
