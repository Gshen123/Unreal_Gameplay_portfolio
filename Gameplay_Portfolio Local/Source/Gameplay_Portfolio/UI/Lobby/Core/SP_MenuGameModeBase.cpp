﻿// Scope Portfolio. All rights reserved


#include "SP_MenuGameModeBase.h"

#include "SP_MenuPlayerController.h"
#include "SP_MenuHUD.h"

ASP_MenuGameModeBase::ASP_MenuGameModeBase()
{
    PlayerControllerClass = ASP_MenuPlayerController::StaticClass();
    HUDClass = ASP_MenuHUD::StaticClass();
}
