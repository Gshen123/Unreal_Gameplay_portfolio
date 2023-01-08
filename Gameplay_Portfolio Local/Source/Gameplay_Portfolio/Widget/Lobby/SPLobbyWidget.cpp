// Fill out your copyright notice in the Description page of Project Settings.


#include "SPLobbyWidget.h"

void USPLobbyWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USPLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(StartButton) StartButton->ScopeOnClicked.AddUniqueDynamic(this, &USPLobbyWidget::GameStart);
	if(LoadButton) LoadButton->ScopeOnClicked.AddUniqueDynamic(this, &USPLobbyWidget::LoadGame);
	if(OptionButton) OptionButton->ScopeOnClicked.AddUniqueDynamic(this, &USPLobbyWidget::LoadOptionWidget);
	if(ExitButton) ExitButton->ScopeOnClicked.AddUniqueDynamic(this, &USPLobbyWidget::ExitGame);
}

void USPLobbyWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void USPLobbyWidget::GameStart()
{
}

void USPLobbyWidget::LoadGame()
{
	
}

void USPLobbyWidget::LoadOptionWidget()
{
	UE_LOG(LogTemp, Log, TEXT("TEST"));
}

void USPLobbyWidget::ExitGame()
{
	auto PC = GetOwningPlayer();
	PC->ConsoleCommand("quit");
}

