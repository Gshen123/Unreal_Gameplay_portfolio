// Scope Portfolio. All rights reserved

#pragma once

#include "SP_BasePlayerController.h"
#include "SP_MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_MenuPlayerController : public ASP_BasePlayerController
{
    GENERATED_BODY()
    
protected:
    ASP_MenuPlayerController(const FObjectInitializer& ObjectInitializer);

    virtual void SetupInputComponent() override;
    
    virtual void BeginPlay() override;
};
