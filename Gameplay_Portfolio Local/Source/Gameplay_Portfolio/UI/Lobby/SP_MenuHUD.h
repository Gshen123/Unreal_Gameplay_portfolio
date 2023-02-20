// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_HUDBase.h"
#include "SP_MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_MenuHUD : public ASP_HUDBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;
    
    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OpenOptionMenu();
};
