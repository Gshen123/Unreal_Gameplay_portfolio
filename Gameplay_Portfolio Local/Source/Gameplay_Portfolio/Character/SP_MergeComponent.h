// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_MergeComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GAMEPLAY_PORTFOLIO_API USP_MergeComponent : public UActorComponent
{

private:
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    
    USkeletalMeshComponent* GetClothMesh() const;
    USkeletalMeshComponent* GetOwnerMesh() const;
    
    UFUNCTION()
    void UpdateMesh(USkeletalMesh* NewMesh) const;

    UFUNCTION()
    void SetMorphTarget(FName MorphTargetName, float Value, bool RemoveWeight = true) const;

    UFUNCTION()
    void ClearMorphTarget();

    void UpdateAnimation(UAnimationAsset* Asset);
};
