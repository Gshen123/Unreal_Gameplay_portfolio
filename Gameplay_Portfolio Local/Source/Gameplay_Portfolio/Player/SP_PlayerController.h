// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay_Portfolio/System/SP_HUD.h"
#include "SP_PlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEPLAY_PORTFOLIO_API ASP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void ToggleGamePause();

	void VisibleExitModal();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASP_HUD* SP_HUD;
};
