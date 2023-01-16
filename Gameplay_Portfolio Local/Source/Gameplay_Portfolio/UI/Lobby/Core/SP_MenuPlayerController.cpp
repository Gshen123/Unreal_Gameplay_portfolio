// Scope Portfolio. All rights reserved


#include "SP_MenuPlayerController.h"

#include "SP_MenuHUD.h"


void ASP_MenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameAndUI());
    bShowMouseCursor = true;
}

void ASP_MenuPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("GamePause", IE_Pressed, this, &ThisClass::PopWidgetStack);
}

void ASP_MenuPlayerController::PopWidgetStack()
{
    auto HUD = Cast<ASP_MenuHUD>(GetHUD());
    HUD->PopWidgetStack();
}
