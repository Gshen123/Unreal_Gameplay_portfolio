// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "SP_HUDBase.h"
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

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> PauseMenuClass;
    
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> GameOverWidgetClass;

private:
    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;
    
    UPROPERTY()
    TMap<EGameModeType, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* PauseMenu;
    
    UPROPERTY()
    UUserWidget* GameOverWidget;
};
