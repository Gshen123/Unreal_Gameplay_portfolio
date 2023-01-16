// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SP_ModularGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_ModularGameMode : public AGameModeBase
{
    GENERATED_BODY()

    ASP_ModularGameMode();

    virtual void StartPlay() override;
};
