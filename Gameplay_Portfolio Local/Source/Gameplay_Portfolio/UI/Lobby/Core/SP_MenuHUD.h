// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SP_MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_MenuHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;
    
    virtual void BeginPlay() override;
};
