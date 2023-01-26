// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SP_BaseCharacter.generated.h"



UCLASS(config=Game)
class ASP_BaseCharacter : public ACharacter
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class UMergeComponent* MergeComponent;
    
public:
    ASP_BaseCharacter();

protected:
    // To add mapping context
    virtual void BeginPlay() override;

public:
    UFUNCTION()
    void UpdateMesh(USkeletalMesh* NewMesh);
};

