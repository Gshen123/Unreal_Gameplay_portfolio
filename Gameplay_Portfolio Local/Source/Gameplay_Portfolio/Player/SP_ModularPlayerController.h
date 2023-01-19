// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_GameInstance.h"
#include "SP_ModularPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_ModularPlayerController : public APlayerController
{
    GENERATED_BODY()

    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

private:

    void GotoOnMenu();

    USP_GameInstance* GetSP_GameInstance() const;
};
