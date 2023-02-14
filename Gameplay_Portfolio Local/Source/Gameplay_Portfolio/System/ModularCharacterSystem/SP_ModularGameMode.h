// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_GameModeBase.h"
#include "SP_ModularGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_ModularGameMode : public ASP_GameModeBase
{
    GENERATED_BODY()

    ASP_ModularGameMode();

    virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
