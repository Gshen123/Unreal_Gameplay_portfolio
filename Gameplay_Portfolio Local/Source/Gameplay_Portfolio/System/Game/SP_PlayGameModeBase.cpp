// Copyright Epic Games, Inc. All Rights Reserved.

#include "SP_PlayGameModeBase.h"
#include "SP_PlayerController.h"
#include "Gameplay_Portfolio/Character/SP_BaseCharacter.h"
#include "Gameplay_Portfolio/UI/Game/SP_GameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SPGameModeBase, All, All);

ASP_PlayGameModeBase::ASP_PlayGameModeBase()
{
    DefaultPawnClass = ASP_BaseCharacter::StaticClass();
    PlayerControllerClass = ASP_PlayerController::StaticClass();
    HUDClass = ASP_GameHUD::StaticClass();
}

void ASP_PlayGameModeBase::StartPlay()
{
    Super::StartPlay();

    SetGameModeType(EGameModeType::MainMenu);
}

EGameModeType ASP_PlayGameModeBase::GetPrevMode() const
{
    return PrevGameMode;
}

void ASP_PlayGameModeBase::SetGameModeType(EGameModeType Tpye)
{
    if(GameModeState == Tpye) return;

    GameModeState = Tpye;
    if(GameModeState != EGameModeType::None && GameModeState != EGameModeType::Pause) PrevGameMode = GameModeState;
    OnGameModeStateChanged.Broadcast(Tpye);
}

bool ASP_PlayGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if(PauseSet)
    {
        SetGameModeType(EGameModeType::Pause);
    }

    return PauseSet;
}

bool ASP_PlayGameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();

    if(PauseCleared)
    {
        SetGameModeType(PrevGameMode);
        UE_LOG(Log_SPGameModeBase, Display, TEXT("PrevGameMode : %s"), *UEnum::GetValueAsString(PrevGameMode));
    }

    return PauseCleared;
}


