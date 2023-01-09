// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_PlayerController.h"

#include "GameFramework/GameUserSettings.h"
#include "Gameplay_Portfolio/System/SP_HUD.h"

void ASP_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ASP_PlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ASP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto SP_HUD = Cast<ASP_HUD>(MyHUD);
	SP_HUD->ShowMainMenu();
}
