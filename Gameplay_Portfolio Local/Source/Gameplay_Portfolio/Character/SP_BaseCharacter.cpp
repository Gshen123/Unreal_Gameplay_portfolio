// Copyright Epic Games, Inc. All Rights Reserved.

#include "SP_BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MergeComponent.h"


//////////////////////////////////////////////////////////////////////////
// AGameplay_PortfolioCharacter

ASP_BaseCharacter::ASP_BaseCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
    MergeComponent = CreateDefaultSubobject<UMergeComponent>(TEXT("MeshComponent"));
    ClothMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ClothMesh"));
    ClothMesh->SetupAttachment(GetMesh());
}

USkeletalMeshComponent* ASP_BaseCharacter::GetClothMesh() const
{
    return  ClothMesh;
}

void ASP_BaseCharacter::BeginPlay()
{
    // Call the base class  
    Super::BeginPlay();
}

void ASP_BaseCharacter::UpdateMesh(USkeletalMesh* NewMesh) const
{
    MergeComponent->UpdateMesh(NewMesh);
}



