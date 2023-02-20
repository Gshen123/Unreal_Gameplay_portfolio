// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Game/SP_PlayGameModeBase.h"
#include "Gameplay_Portfolio/UI/System/SP_PauseWidget.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SPGameHUD, All, All);

void ASP_GameHUD::BeginPlay()
{
    Super::BeginPlay();

    PauseMenu = CreateWidget<USP_PauseWidget>(GetWorld(), PauseMenuClass);
    PauseMenu->SetVisibility(ESlateVisibility::Hidden);
    PauseMenu->AddToViewport();
    PauseMenu->OptionButton->OnClicked.AddDynamic(this, &ASP_GameHUD::OpenOptionMenu);
    PauseMenu->ClearPauseButton->OnClicked.AddDynamic(this, &ASP_GameHUD::HidePauseWidget);

    GameOverWidget = CreateWidget<USP_GameOverWidget>(GetWorld(), GameOverWidgetClass);
    GameOverWidget->SetVisibility(ESlateVisibility::Hidden);
    GameOverWidget->AddToViewport();
    RemoveWidgetInStack(GameOverWidget);
    
    if(GetWorld())
        if(const auto GameMode = Cast<ASP_PlayGameModeBase>(GetWorld()->GetAuthGameMode()))
            GameMode->OnGameModeStateChanged.AddUObject(this, &ThisClass::OnGameModeTypeChanged);
}

void ASP_GameHUD::OnGameModeTypeChanged(EGameModeType Type)
{
    if(Type == EGameModeType::Pause)
        PushWidgetStack(PauseMenu);
    else if(Type == EGameModeType::GameOver)
        PushWidgetStack(GameOverWidget);
    else PopWidgetStack();
}

void ASP_GameHUD::HidePauseWidget()
{
    RemoveWidgetInStack(PauseMenu);
}

void ASP_GameHUD::OpenOptionMenu()
{
    ShowOptionMenu(false);
}
