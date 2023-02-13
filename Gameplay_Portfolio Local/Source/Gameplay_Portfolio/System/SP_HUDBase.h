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
    
    UFUNCTION(BlueprintCallable)
    void ShowOptionMenu();
	
    UFUNCTION(BlueprintCallable)
    void HideOptionMenu();

    
    UFUNCTION()
    void PushWidgetStack(UUserWidget* Widget);

    UFUNCTION()
    UUserWidget* PopWidgetStack();

    UFUNCTION()
    void RemoveWidgetInStack(UUserWidget* Widget);
    
protected:

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> OptionMenuClass;

private:
    UPROPERTY()
    UUserWidget* OptionMenu;

    //임시용
    UPROPERTY()
    UUserWidget* CurrentVisibleWidget;
    
    TArray<UUserWidget*> WidgetStack;
    
    UFUNCTION()
    void AllHideWidget();
};


