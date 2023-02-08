﻿// Scope Portfolio. All rights reserved


#include "SP_ModularPlayerController.h"

#include "SP_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void ASP_ModularPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
    bShowMouseCursor = true;
    Cast<ASP_PlayerCharacter>(GetCharacter())->ToggleCameraMode();
}

void ASP_ModularPlayerController::GotoOnMenu() const
{
    const auto GameInstance = GetSP_GameInstance();
    if(!GameInstance) return;
    
    UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelData().LevelName);
}


USP_GameInstance* ASP_ModularPlayerController::GetSP_GameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USP_GameInstance>();
}
