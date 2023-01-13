// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameHUD.h"

#include "SP_GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/UI/Lobby/SP_MainMenuWidget.h"
#include "Gameplay_Portfolio/UI/System/SP_MainOptionWidget.h"
#include "Gameplay_Portfolio/UI/System/SP_PauseWidget.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SPHUD, All, All);

void ASP_GameHUD::BeginPlay()
{
    Super::BeginPlay();

    const auto MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
    const auto LobbyMenu = Cast<USP_MainMenuWidget>(MainMenu);
    LobbyMenu->MainMenuOptionDelegate.AddUniqueDynamic(this, &ASP_GameHUD::ShowOptionMenu);
    GameWidgets.Add(EGameModeType::MainMenu, MainMenu);

    GameWidgets.Add(EGameModeType::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseMenuClass));
    const auto PauseWidget = Cast<USP_PauseWidget>(MainMenu);
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
        if(const auto GameMode = Cast<ASP_GameModeBase>(GetWorld()->GetAuthGameMode()))
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

void ASP_GameHUD::ShowOptionMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	OptionMenu = CreateWidget<UUserWidget>( PC, OptionMenuClass );
	OptionMenu->AddToViewport();

	auto OptionWidget = Cast<USP_MainOptionWidget>(OptionMenu);
	OptionWidget->GraphicTabBtn->SetFocus();
	OptionWidget->ExitBtn->OnClicked.AddUniqueDynamic(this, &ASP_GameHUD::HideOptionMenu);
}

void ASP_GameHUD::HideOptionMenu()
{
	if (OptionMenu)
	{
		OptionMenu->RemoveFromParent();
		OptionMenu = nullptr;
	}
}