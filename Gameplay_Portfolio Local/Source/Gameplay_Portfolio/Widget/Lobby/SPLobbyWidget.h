// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPMediaWidget.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/Widget/SPTextButton.h"
#include "SPLobbyWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEPLAY_PORTFOLIO_API USPLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TSoftObjectPtr<USPMediaWidget> MediaWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TSoftObjectPtr<USPTextButton> StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TSoftObjectPtr<USPTextButton> LoadButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TSoftObjectPtr<USPTextButton> OptionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TSoftObjectPtr<USPTextButton> ExitButton;

	void GameStart();

	void LoadGame();

	void CreateOptionWidget();

	void ExitGame();
	
};
