// Scope Portfolio. All rights reserved


#include "SP_MenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/UI/Lobby/SP_MainMenuWidget.h"

void ASP_MenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if(MenuWidgetClass)
    {
        if(const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass))
        {
            MenuWidget->AddToViewport();
            const auto LobbyMenu = Cast<USP_MainMenuWidget>(MenuWidget);
            LobbyMenu->OptionButton->MainButton->OnClicked.AddDynamic(this, &ASP_MenuHUD::OpenOptionMenu);
            //GameWidgets.Add(EGameModeType::MainMenu, MainMenu);
        }
    }
}

void ASP_MenuHUD::OpenOptionMenu()
{
    ShowOptionMenu(true);
}
