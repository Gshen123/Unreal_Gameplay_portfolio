// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Game/SP_PlayGameModeBase.h"
#include "Gameplay_Portfolio/UI/System/SP_PauseWidget.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SPHUD, All, All);

void ASP_GameHUD::BeginPlay()
{
    Super::BeginPlay();

    PauseMenu = CreateWidget<UUserWidget>(GetWorld(), PauseMenuClass);
    const auto PauseWidget = Cast<USP_PauseWidget>(PauseMenu);
    GameWidgets.Add(EGameModeType::Pause, PauseMenu);
    PauseWidget->PauseWidgetOptionDelegate.AddUniqueDynamic(this, &ASP_GameHUD::ShowOptionMenu);
    
    GameWidgets.Add(EGameModeType::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));
    
    for(auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if(!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if(GetWorld())
    {
        if(const auto GameMode = Cast<ASP_PlayGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnGameModeStateChanged.AddUObject(this, &ThisClass::OnGameModeTypeChanged);
        }
    }
}

void ASP_GameHUD::OnGameModeTypeChanged(EGameModeType Type)
{
    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if(GameWidgets.Contains(Type))
    {
        CurrentWidget = GameWidgets[Type];
    }

    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
    
    UE_LOG(Log_SPHUD, Display, TEXT("Game Mode State Changed : %s"), *UEnum::GetValueAsString(Type));
}
