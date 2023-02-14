// Scope Portfolio. All rights reserved

#pragma once

#include "SP_BasePlayerController.h"
#include "SP_GameInstance.h"
#include "SP_ModularPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_ModularPlayerController : public ASP_BasePlayerController
{
    GENERATED_BODY()

protected:
    ASP_ModularPlayerController(const FObjectInitializer& ObjectInitializer);

    virtual void SetupInputComponent() override;
    
    virtual void BeginPlay() override;
};
