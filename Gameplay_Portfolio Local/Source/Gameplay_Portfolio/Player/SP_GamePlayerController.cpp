// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GamePlayerController.h"
#include "Game/SP_PlayGameModeBase.h"
#include "Gameplay_Portfolio/EnhancedInput/SP_InputComponent.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SPPlayerController, All, All);

ASP_GamePlayerController::ASP_GamePlayerController(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    Type = EGameModeType::InGame;
}

void ASP_GamePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("PauseAndUndo", IE_Pressed, this, &ThisClass::PopWidgetStack).bExecuteWhenPaused = true;
}

void ASP_GamePlayerController::BeginPlay()
{
    Super::BeginPlay();

    if(GetWorld())
        if(const auto GameMode = Cast<ASP_PlayGameModeBase>(GetWorld()->GetAuthGameMode()))
            GameMode->OnGameModeStateChanged.AddUObject(this, &ThisClass::OnGameModeTypeChanged);
}

void ASP_GamePlayerController::OnPauseGame()
{
    const auto GameMode = GetWorld()->GetAuthGameMode();
    if(!GetWorld() || !GameMode) return;

    IsPaused()
        ? GameMode->ClearPause()
        : GameMode->SetPause(this);;

    UE_LOG(Log_SPPlayerController, Display, TEXT("OnPauseGame !"));
}

void ASP_GamePlayerController::OnGameModeTypeChanged(EGameModeType ChangeType)
{
    if(ChangeType == EGameModeType::InGame)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else if(ChangeType == EGameModeType::MainMenu)
    {
        SetInputMode(FInputModeGameAndUI());
        bShowMouseCursor = true;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}