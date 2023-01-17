// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_AssetManager.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "SP_ItemModule_Suit.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GAMEPLAY_PORTFOLIO_API USP_ItemModule_Suit : public USP_ModularItemBase
{
    GENERATED_BODY()

public:
    USP_ItemModule_Suit()
    {
        Data.ItemType = USP_AssetManager::Module_SuitType;
        Data.OverlapBody = true;
        Data.OccupiedParts = static_cast<int8>(EOccupiedParts::hasTop) | static_cast<int8>(EOccupiedParts::hasBottom) |
                             static_cast<int8>(EOccupiedParts::hasFeetAndLeg) | static_cast<int8>(EOccupiedParts::hasHandAndArm);
    }
    
};
