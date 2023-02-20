// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SP_HUDBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_HUDBase : public AHUD
{
    GENERATED_BODY()

public:
    
    UFUNCTION()
    void PushWidgetStack(UUserWidget* Widget, bool HideOther = true);

    UFUNCTION()
    UUserWidget* PopWidgetStack();

    UFUNCTION()
    void RemoveWidgetInStack(UUserWidget* Widget);
    
protected:

    UFUNCTION()
    void ShowOptionMenu(bool HideOther);

    UFUNCTION()
    void HideOptionMenu();
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> OptionMenuClass;

private:
    UPROPERTY()
    UUserWidget* OptionMenu;
    
    TArray<UUserWidget*> WidgetStack;
    
    UFUNCTION()
    void AllHideWidget();
};


