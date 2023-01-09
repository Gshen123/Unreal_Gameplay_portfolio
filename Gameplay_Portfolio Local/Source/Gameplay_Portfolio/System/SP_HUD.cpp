// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_HUD.h"

#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/Widget/Lobby/SPLobbyOptionWidget.h"
#include "Gameplay_Portfolio/Widget/Lobby/SPLobbyWidget.h"

void ASP_HUD::ShowMainMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	MainMenu = CreateWidget<UUserWidget>( PC, MainMenuClass );
	MainMenu->AddToViewport();

	auto LobbyMenu = Cast<USPLobbyWidget>(MainMenu);
	LobbyMenu->StartButton->SetFocus();
	LobbyMenu->OptionButton->MainButton->OnClicked.AddUniqueDynamic(this, &ASP_HUD::ShowOptionMenu);
	
	SetInputModeUIOnly(PC);
}

void ASP_HUD::HideMainMenu()
{
	if (MainMenu)
	{
		MainMenu->RemoveFromParent();
		MainMenu = nullptr;
	}
}

void ASP_HUD::ShowOptionMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	OptionMenu = CreateWidget<UUserWidget>( PC, OptionMenuClass );
	OptionMenu->AddToViewport();

	auto OptionWidget = Cast<USPLobbyOptionWidget>(OptionMenu);
	OptionWidget->ExitBtn->OnClicked.AddUniqueDynamic(this, &ASP_HUD::HideOptionMenu);
	
	SetInputModeUIOnly(PC);
	//auto OptionWidget = Cast<USPLobbyOptionWidget>(MainMenu);
	//OptionWidget->SetFocus();
}

void ASP_HUD::HideOptionMenu()
{
	if (OptionMenu)
	{
		OptionMenu->RemoveFromParent();
		OptionMenu = nullptr;
	}
}

void ASP_HUD::SetInputModeUIOnly(APlayerController* PC)
{
	const FInputModeUIOnly inputMode;
	PC->SetInputMode(inputMode);
	PC->SetShowMouseCursor(true);
}

void ASP_HUD::SetInputModeGameAndUI(APlayerController* PC)
{
	const FInputModeGameAndUI inputMode;
	PC->SetInputMode(inputMode);
	PC->SetShowMouseCursor(true);
}

void ASP_HUD::SetInputModeGameOnly(APlayerController* PC)
{
	const FInputModeGameOnly inputMode;
	PC->SetInputMode(inputMode);
	PC->SetShowMouseCursor(false);
}
