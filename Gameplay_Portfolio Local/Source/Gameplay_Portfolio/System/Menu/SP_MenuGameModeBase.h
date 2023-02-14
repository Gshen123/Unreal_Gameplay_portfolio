// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_GameModeBase.h"
#include "SP_MenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_MenuGameModeBase : public ASP_GameModeBase
{
    GENERATED_BODY()

public:
    ASP_MenuGameModeBase();

    virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
