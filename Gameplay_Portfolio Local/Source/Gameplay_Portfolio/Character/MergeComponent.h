// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "MergeComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API UMergeComponent : public UActorComponent
{

private:
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    
    UFUNCTION()
    void UpdateMesh(USkeletalMesh* NewMesh);
};
