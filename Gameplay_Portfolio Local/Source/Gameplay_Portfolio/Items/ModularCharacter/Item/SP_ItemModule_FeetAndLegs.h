// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_AssetManager.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "SP_ItemModule_FeetAndLegs.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GAMEPLAY_PORTFOLIO_API USP_ItemModule_FeetAndLegs : public USP_ModularItemBase
{
    GENERATED_BODY()

public:
    USP_ItemModule_FeetAndLegs()
    {
        Data.ItemType = USP_AssetManager::Module_FeetAndLegsType;
        Data.WearStatus = static_cast<int32>(EWearStatus::hasFeetAndLeg);
    }
    
};
