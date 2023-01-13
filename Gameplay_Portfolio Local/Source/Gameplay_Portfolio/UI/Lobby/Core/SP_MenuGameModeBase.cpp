// Scope Portfolio. All rights reserved


#include "SP_MenuGameModeBase.h"

#include "SP_MainMenuPlayerController.h"
#include "SP_MenuHUD.h"

ASP_MenuGameModeBase::ASP_MenuGameModeBase()
{
    PlayerControllerClass = ASP_MainMenuPlayerController::StaticClass();
    HUDClass = ASP_MenuHUD::StaticClass();
}
