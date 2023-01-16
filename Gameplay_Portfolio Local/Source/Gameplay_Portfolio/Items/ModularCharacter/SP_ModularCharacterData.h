// Scope Portfolio. All rights reserved

#pragma once
#include "GameplayTagContainer.h"

#include "SP_ModularCharacterData.generated.h"

/**
 * 
 */
USTRUCT()
struct FModularItemConditions
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, DisplayName = "필요 레벨", meta = (ClampMin = 0, ClampMax = 5, UIMin = 0, UIMax = 5))
    int Level = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "필요 게임플레이 태그", meta = (Categories = "Dress"))
    TArray<FGameplayTag> Tags;
};
