// Scope Portfolio. All rights reserved


#include "SP_MenuPlayerController.h"
#include "Gameplay_Portfolio/UI/Lobby/SP_MenuHUD.h"


void ASP_MenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
    bShowMouseCursor = true;
}

void ASP_MenuPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("GamePause", IE_Pressed, this, &ThisClass::PopWidgetStack);
}

void ASP_MenuPlayerController::PopWidgetStack()
{
    const auto HUD = Cast<ASP_MenuHUD>(GetHUD());
    HUD->PopWidgetStack();
}
