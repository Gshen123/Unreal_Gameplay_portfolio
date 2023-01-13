// Scope Portfolio. All rights reserved


#include "SP_MenuHUD.h"

#include "Blueprint/UserWidget.h"

void ASP_MenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if(MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        if(MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}
