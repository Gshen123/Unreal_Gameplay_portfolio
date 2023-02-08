// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SP_CoreType.h"
#include "SP_BasePlayerController.h"
#include "SP_GamePlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEPLAY_PORTFOLIO_API ASP_GamePlayerController : public ASP_BasePlayerController
{
    GENERATED_BODY()
    
protected:

    virtual void SetupInputComponent() override;
	
    virtual void BeginPlay() override;

private:
    void OnPauseGame();
    void OnGameModeTypeChanged(EGameModeType State);
};
