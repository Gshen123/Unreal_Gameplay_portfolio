// Scope Portfolio. All rights reserved


#include "SP_MenuPlayerController.h"

ASP_MenuPlayerController::ASP_MenuPlayerController(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    Type = EGameModeType::MainMenu;
}

void ASP_MenuPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("PauseAndUndo", IE_Pressed, this, &ThisClass::PopWidgetStack);
}

void ASP_MenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
    bShowMouseCursor = true;
}

