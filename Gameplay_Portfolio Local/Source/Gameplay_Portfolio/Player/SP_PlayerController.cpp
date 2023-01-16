// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_PlayerController.h"
#include "Gameplay_Portfolio/System/SP_GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SPPlayerController, All, All);

void ASP_PlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void ASP_PlayerController::OnUnPossess()
{
    Super::OnUnPossess();
}

void ASP_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    check(InputComponent);

    //bExecutedWhenPaused는 플레이어 컨트롤의 틱을 중단시킵니다. 일시정지 기능을 보완합니다.
    InputComponent->BindAction("GamePause", IE_Pressed, this, &ThisClass::OnPauseGame).bExecuteWhenPaused = true;
}

void ASP_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    if(GetWorld())
    {
        if(const auto GameMode = Cast<ASP_GameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnGameModeStateChanged.AddUObject(this, &ThisClass::OnGameModeTypeChanged);
        }
    }
}

void ASP_PlayerController::OnPauseGame()
{
    const auto GameMode = GetWorld()->GetAuthGameMode();
    if(!GetWorld() || !GameMode) return;

    IsPaused()
        ? GameMode->ClearPause()
        : GameMode->SetPause(this);;

    UE_LOG(Log_SPPlayerController, Display, TEXT("OnPauseGame !"));
}

void ASP_PlayerController::OnGameModeTypeChanged(EGameModeType Type)
{
    if(Type == EGameModeType::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else if(Type == EGameModeType::MainMenu)
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