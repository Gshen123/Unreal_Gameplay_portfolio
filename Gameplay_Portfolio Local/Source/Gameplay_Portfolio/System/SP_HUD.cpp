// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_HUD.h"

#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/Widget/Lobby/SPLobbyWidget.h"
#include "Gameplay_Portfolio/Widget/System/SP_ExitModal.h"
#include "Gameplay_Portfolio/Widget/System/SP_MainOptionWidget.h"

void ASP_HUD::ShowMainMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	MainMenu = CreateWidget<UUserWidget>( PC, MainMenuClass );
	MainMenu->AddToViewport();

	auto LobbyMenu = Cast<USPLobbyWidget>(MainMenu);
	LobbyMenu->StartButton->SetFocus();
	LobbyMenu->OptionButton->MainButton->OnClicked.AddUniqueDynamic(this, &ASP_HUD::ShowOptionMenu);
	LobbyMenu->ExitButton->MainButton->OnClicked.AddUniqueDynamic(this, &ASP_HUD::ShowExitModal);
	
	SetInputModeGameAndUI(PC);
}

void ASP_HUD::HideMainMenu()
{
	if (MainMenu)
	{
		MainMenu->RemoveFromParent();
		MainMenu = nullptr;
	}
}

bool ASP_HUD::IsActiveMainMenu() const
{
	if (MainMenu)
	{
		return true;
	}
	return false;
}

void ASP_HUD::ShowOptionMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	OptionMenu = CreateWidget<UUserWidget>( PC, OptionMenuClass );
	OptionMenu->AddToViewport();

	auto OptionWidget = Cast<USP_MainOptionWidget>(OptionMenu);
	OptionWidget->GraphicTabBtn->SetFocus();
	OptionWidget->ExitBtn->OnClicked.AddUniqueDynamic(this, &ASP_HUD::HideOptionMenu);
	SetInputModeGameAndUI(PC);
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

void ASP_HUD::ShowExitModal()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	ExitModal = CreateWidget<UUserWidget>( PC, ExitModalClass );
	ExitModal->AddToViewport();

	auto ExitModalWidget = Cast<USP_ExitModal>(ExitModal);
	ExitModalWidget->NoButton->SetFocus();
	ExitModalWidget->YesButton->MainButton->OnClicked.AddUniqueDynamic(this, &ASP_HUD::ExitGame);
	ExitModalWidget->NoButton->MainButton->OnClicked.AddUniqueDynamic(this, &ASP_HUD::HideExitModal);
	SetInputModeGameAndUI(PC);
}

void ASP_HUD::HideExitModal()
{
	if (ExitModal)
	{
		ExitModal->RemoveFromParent();
		ExitModal = nullptr;
	}
}

bool ASP_HUD::IsActiveExitModal() const
{
	if(ExitModal)
	{
		return true;
	}
	return false;
}

void ASP_HUD::ExitGame()
{
	auto PC = GetOwningPlayerController();
	PC->ConsoleCommand("quit");
}

void ASP_HUD::ShowPauseMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	PauseMenu = CreateWidget<UUserWidget>( PC, PauseMenuClass );
	PauseMenu->AddToViewport();
}

void ASP_HUD::HidePauseMenu()
{
	if (PauseMenu)
	{
		PauseMenu->RemoveFromParent();
		PauseMenu = nullptr;
	}
}

bool ASP_HUD::IsActivePauseMenu() const
{
	if (PauseMenu)
	{
		return true;
	}
	return false;
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