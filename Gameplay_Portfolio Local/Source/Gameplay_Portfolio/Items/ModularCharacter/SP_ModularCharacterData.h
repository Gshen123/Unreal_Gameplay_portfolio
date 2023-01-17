// Scope Portfolio. All rights reserved

#pragma once
#include "GameplayTagContainer.h"
#include "SP_ModularCharacterData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FModularItemConditions
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, DisplayName = "요구 레벨", meta = (ClampMin = 0, ClampMax = 5, UIMin = 0, UIMax = 5))
    int Level = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "요구되는 게임 플레이 태그", meta = (Categories = "Dress"))
    TArray<FGameplayTag> Tags;
};
