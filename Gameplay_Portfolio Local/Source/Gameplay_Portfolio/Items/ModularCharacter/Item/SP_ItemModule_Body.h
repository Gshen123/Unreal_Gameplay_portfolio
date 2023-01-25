// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_AssetManager.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "SP_ItemModule_Body.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GAMEPLAY_PORTFOLIO_API USP_ItemModule_Body : public USP_ModularItemBase
{
    GENERATED_BODY()

public:
    USP_ItemModule_Body()
    {
        Data.ItemType = USP_AssetManager::Module_BodyType;
        Data.WearStatus = static_cast<int32>(EWearStatus::hasBody);
    }
    
};
