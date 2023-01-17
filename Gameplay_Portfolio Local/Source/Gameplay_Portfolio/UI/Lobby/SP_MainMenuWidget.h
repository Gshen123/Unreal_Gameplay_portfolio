// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SP_GameInstance.h"
#include "SP_LevelItemBox.h"
#include "SP_LevelItemWidget.h"
#include "SP_MenuHUD.h"
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

    UPROPERTY(meta = (BindWidget))
    USP_LevelItemBox* LevelItemBox;
    
    UFUNCTION()
    void LoadGame();
	
    UFUNCTION()
    void ShowOptionWidget();

    UFUNCTION()
    void ShowExitModal();

    UFUNCTION()
    void ShowSelectedLevel();

    UPROPERTY()
    FMainMenuOption MainMenuOptionDelegate;
    
protected:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> ExitModalClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> LevelItemWidgetClass;
    
private:
    UPROPERTY()
    UUserWidget* ExitModal;

    UPROPERTY()
    TArray<USP_LevelItemWidget*> LevelItemWidgets;

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    
    USP_GameInstance* GetSP_GameInstance() const;
    ASP_MenuHUD* GetSP_MenuHUD() const;

    bool SelectedLevel = false;
};
