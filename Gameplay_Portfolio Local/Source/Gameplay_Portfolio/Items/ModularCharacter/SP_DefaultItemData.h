// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SP_DefaultItemData.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_DefaultItemData : public UObject
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "다리", Category = "Defaults|Legs" )
    TSoftObjectPtr<USkeletalMesh> Legs;
};
