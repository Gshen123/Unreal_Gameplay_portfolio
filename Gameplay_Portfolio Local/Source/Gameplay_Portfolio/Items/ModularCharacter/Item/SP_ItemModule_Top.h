// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_AssetManager.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "SP_ItemModule_Top.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GAMEPLAY_PORTFOLIO_API USP_ItemModule_Top : public USP_ModularItemBase
{
    GENERATED_BODY()

public:
    USP_ItemModule_Top()
    {
        Data.ItemType = USP_AssetManager::Module_TopType;
        Data.OccupiedParts = static_cast<int8>(EOccupiedParts::hasTop);
    }
    
};
