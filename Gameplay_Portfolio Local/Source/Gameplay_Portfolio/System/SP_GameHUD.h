// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "GameFramework/HUD.h"
#include "SP_GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_GameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    
    void OnGameModeTypeChanged(EGameModeType Type);
    
    UFUNCTION(BlueprintCallable)
    void ShowOptionMenu();
	
    UFUNCTION(BlueprintCallable)
    void HideOptionMenu();

protected:

    ///////////////////////
    ///      Lobby      ///
    ///////////////////////
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> MainMenuClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> OptionMenuClass;

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
    UUserWidget* OptionMenu;

    UPROPERTY()
    UUserWidget* PauseMenu;
    
    UPROPERTY()
    UUserWidget* GameOverWidget;
};
