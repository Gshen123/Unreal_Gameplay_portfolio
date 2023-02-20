// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GamePlayerController.h"
#include "Game/SP_PlayGameModeBase.h"
#include "Gameplay_Portfolio/EnhancedInput/SP_InputComponent.h"
#include "System/SP_PauseWidget.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SPPlayerController, All, All);

ASP_GamePlayerController::ASP_GamePlayerController(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    Type = EGameModeType::InGame;
}

void ASP_GamePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("PauseAndUndo", IE_Pressed, this, &ThisClass::OnPauseGame).bExecuteWhenPaused = true;
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
        ? PopWidgetStack()
        : GameMode->SetPause(this);

    if(Type == EGameModeType::Pause && PopWidget)
        if(Cast<USP_PauseWidget>(PopWidget))
        {
            GameMode->ClearPause();
            PopWidget = nullptr;
        }
    
    UE_LOG(Log_SPPlayerController, Display, TEXT("OnPauseGame !"));
}

void ASP_GamePlayerController::OnGameModeTypeChanged(EGameModeType ChangeType)
{
    Type = ChangeType;
    
    if(ChangeType == EGameModeType::InGame)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else if(ChangeType == EGameModeType::CharacterSetup || ChangeType == EGameModeType::Pause)
    {
        SetInputMode(FInputModeGameAndUI());
        bShowMouseCursor = true;
    }
    else if(ChangeType == EGameModeType::GameOver)
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}