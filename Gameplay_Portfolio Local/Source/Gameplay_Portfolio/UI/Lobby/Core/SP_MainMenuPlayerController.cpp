// Scope Portfolio. All rights reserved


#include "SP_MainMenuPlayerController.h"


void ASP_MainMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameOnly());
    bShowMouseCursor = true;
}
