// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_MenuPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    
    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

private:

    void PopWidgetStack();
};
