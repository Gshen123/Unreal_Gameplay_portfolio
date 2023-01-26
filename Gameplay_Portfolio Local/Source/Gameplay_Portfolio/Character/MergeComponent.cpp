// Scope Portfolio. All rights reserved


#include "MergeComponent.h"

#include "SP_PlayerCharacter.h"
#include "Subsystem/SP_WorldSubsystem.h"

void UMergeComponent::BeginPlay()
{
    Super::BeginPlay();
    const auto WS = GetOwner()->GetWorld()->GetSubsystem<USP_WorldSubsystem>();
    WS->AddMergeComponent(this);
}

void UMergeComponent::UpdateMesh(USkeletalMesh* NewMesh) const
{
    if(auto Chr = Cast<ASP_PlayerCharacter>(GetOwner()))
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
