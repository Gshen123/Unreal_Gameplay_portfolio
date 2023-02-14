// Scope Portfolio. All rights reserved


#include "SP_MenuGameModeBase.h"
#include "SP_MenuPlayerController.h"
#include "Gameplay_Portfolio/UI/Lobby/SP_MenuHUD.h"

ASP_MenuGameModeBase::ASP_MenuGameModeBase()
{
    PlayerControllerClass = ASP_MenuPlayerController::StaticClass();
    HUDClass = ASP_MenuHUD::StaticClass();
}

void ASP_MenuGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}
