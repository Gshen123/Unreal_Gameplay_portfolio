// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "MergeComponent.h"
#include "SP_WorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_WorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    void AddMergeComponent(UMergeComponent* Component);
    
    UFUNCTION()
    TArray<UMergeComponent*> GetMergeComponents();

private:
    UPROPERTY()
    TArray<UMergeComponent*> MergeComponents;
};
