// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_AssetManager.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "SP_ItemModule_Bottom.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GAMEPLAY_PORTFOLIO_API USP_ItemModule_Bottom : public USP_ModularItemBase
{
    GENERATED_BODY()

public:
    USP_ItemModule_Bottom()
    {
        Data.ItemType = USP_AssetManager::Module_BottomType;
        Data.OccupiedParts = static_cast<int8>(EOccupiedParts::hasBottom);
    }
    
};
