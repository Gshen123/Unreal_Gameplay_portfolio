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

    virtual void BeginPlay() override;

private:

    void GotoOnMenu() const;

    USP_GameInstance* GetSP_GameInstance() const;
};
