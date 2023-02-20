// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "SP_GameOverWidget.h"
#include "SP_HUDBase.h"
#include "System/SP_PauseWidget.h"
#include "SP_GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_GameHUD : public ASP_HUDBase
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    
    void OnGameModeTypeChanged(EGameModeType Type);

protected:
    UFUNCTION()
    void HidePauseWidget();

    UFUNCTION()
    void OpenOptionMenu();
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> PauseMenuClass;
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> GameOverWidgetClass;

private:
    
    UPROPERTY()
    USP_PauseWidget* PauseMenu;
    
    UPROPERTY()
    USP_GameOverWidget* GameOverWidget;
};
