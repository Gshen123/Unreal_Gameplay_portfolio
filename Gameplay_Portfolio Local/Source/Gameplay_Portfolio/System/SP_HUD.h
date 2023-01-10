// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SP_HUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_HUD : public AHUD
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void ShowMainMenu();
	
	UFUNCTION(BlueprintCallable)
	void HideMainMenu();

	UFUNCTION(BlueprintCallable)
	void ShowOptionMenu();
	
	UFUNCTION(BlueprintCallable)
	void HideOptionMenu();

	UFUNCTION(BlueprintCallable)
	void ShowExitModal();

	UFUNCTION(BlueprintCallable)
	void HideExitModal();

	UFUNCTION(BlueprintCallable)
	bool IsActiveExitModal() const;
	
	UFUNCTION(BlueprintCallable)
	void ExitGame();

	UFUNCTION(BlueprintCallable)
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable)
	void HidePauseMenu();

	UFUNCTION(BlueprintCallable)
	bool IsActivePauseMenu() const;
	
	static void SetInputModeUIOnly(APlayerController* PC);
	static void SetInputModeGameAndUI(APlayerController* PC);
	static void SetInputModeGameOnly(APlayerController* PC);

protected:

	///////////////////////
	///      Lobby      ///
	///////////////////////
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> OptionMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ExitModalClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> PauseMenuClass;
	
	UPROPERTY()
	UUserWidget* MainMenu;

	UPROPERTY()
	UUserWidget* OptionMenu;

	UPROPERTY()
	UUserWidget* ExitModal;

	UPROPERTY()
	UUserWidget* PauseMenu;
};
