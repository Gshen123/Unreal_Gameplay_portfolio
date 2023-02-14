// Copyright Epic Games, Inc. All Rights Reserved.

#include "SP_PlayGameModeBase.h"
#include "SP_GamePlayerController.h"
#include "Gameplay_Portfolio/Character/SP_PlayerCharacter.h"
#include "Gameplay_Portfolio/UI/Game/SP_GameHUD.h"

ASP_PlayGameModeBase::ASP_PlayGameModeBase()
{
    DefaultPawnClass = ASP_PlayerCharacter::StaticClass();
    PlayerControllerClass = ASP_GamePlayerController::StaticClass();
    HUDClass = ASP_GameHUD::StaticClass();
    CurrentGameMode = EGameModeType::InGame;
}

void ASP_PlayGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}
