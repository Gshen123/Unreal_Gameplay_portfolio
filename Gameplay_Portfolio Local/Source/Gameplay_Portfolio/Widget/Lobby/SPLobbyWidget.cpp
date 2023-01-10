// Fill out your copyright notice in the Description page of Project Settings.


#include "SPLobbyWidget.h"

void USPLobbyWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USPLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(StartButton) StartButton->MainButton->OnClicked.AddUniqueDynamic(this, &USPLobbyWidget::GameStart);
	if(LoadButton) LoadButton->MainButton->OnClicked.AddUniqueDynamic(this, &USPLobbyWidget::LoadGame);
	if(OptionButton) OptionButton->MainButton->OnClicked.AddUniqueDynamic(this, &USPLobbyWidget::LoadOptionWidget);
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
