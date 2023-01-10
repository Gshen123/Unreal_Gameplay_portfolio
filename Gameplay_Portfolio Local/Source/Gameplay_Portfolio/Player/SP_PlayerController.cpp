// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_PlayerController.h"
#include "Gameplay_Portfolio/System/SP_HUD.h"

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
	InputComponent->BindAction("ToggleGamePause", IE_Pressed, this, &ThisClass::ToggleGamePause).bExecuteWhenPaused = true;
	InputComponent->BindAction("Exit", IE_Pressed, this, &ThisClass::ToggleGamePause);
}

void ASP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SP_HUD = Cast<ASP_HUD>(MyHUD);
	check(SP_HUD);
	SP_HUD->ShowMainMenu();
}

void ASP_PlayerController::ToggleGamePause()
{
	SetPause(!IsPaused());
	bShowMouseCursor = IsPaused();
	IsPaused()
		? SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false))
		: SetInputMode(FInputModeGameOnly());

	IsPaused()
	?  SP_HUD->IsActivePauseMenu()
			? nullptr : SP_HUD->ShowPauseMenu()
	:  SP_HUD->IsActivePauseMenu()
			? SP_HUD->HidePauseMenu() : nullptr;

}

void ASP_PlayerController::VisibleExitModal()
{
	if(SP_HUD->IsActiveExitModal())
	{
		SP_HUD->HideExitModal();
	}
	else
	{
		SP_HUD->ShowExitModal();
	}
}
