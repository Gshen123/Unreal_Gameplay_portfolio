// Scope Portfolio. All rights reserved


#include "SP_MenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/UI/Lobby/SP_MainMenuWidget.h"

void ASP_MenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if(MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        if(MenuWidget)
        {
            MenuWidget->AddToViewport();
            const auto LobbyMenu = Cast<USP_MainMenuWidget>(MenuWidget);
            LobbyMenu->MainMenuOptionDelegate.AddUniqueDynamic(this, &ASP_MenuHUD::ShowOptionMenu);
            //GameWidgets.Add(EGameModeType::MainMenu, MainMenu);
        }
    }
}
