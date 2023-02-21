// Scope Portfolio. All rights reserved


#include "SP_ModularPlayerController.h"
#include "SP_PlayerCharacter.h"

ASP_ModularPlayerController::ASP_ModularPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Type = EGameModeType::CharacterSetup;
}

void ASP_ModularPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("PauseAndUndo", IE_Pressed, this, &ThisClass::PopWidgetStack);
}

void ASP_ModularPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
    bShowMouseCursor = true;
}
