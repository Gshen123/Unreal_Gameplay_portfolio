// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"
#include "SP_MainMenuWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMainMenuOption);
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEPLAY_PORTFOLIO_API USP_MainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    
    virtual void NativeConstruct() override;
	
    UPROPERTY(meta = (BindWidget))
    USP_TextButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* LoadButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* OptionButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ExitButton;

    UFUNCTION()
    void GameStart();
	
    UFUNCTION()
    void LoadGame();
	
    UFUNCTION()
    void ShowOptionWidget();

    UFUNCTION()
    void ShowExitModal();

    UPROPERTY()
    FMainMenuOption MainMenuOptionDelegate;
    
protected:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> ExitModalClass;
    
private:
    UPROPERTY()
    UUserWidget* ExitModal;
};
