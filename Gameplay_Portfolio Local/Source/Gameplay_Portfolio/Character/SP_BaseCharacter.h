// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SP_BaseCharacter.generated.h"



UCLASS()
class ASP_BaseCharacter : public ACharacter
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class UMergeComponent* MergeComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent* ClothMesh;
    
public:
    ASP_BaseCharacter();

    USkeletalMeshComponent* GetClothMesh() const;

protected:
    // To add mapping context
    virtual void BeginPlay() override;

public:
    UFUNCTION()
    void UpdateMesh(USkeletalMesh* NewMesh) const;
};

