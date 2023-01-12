// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/Widget/SP_TextButton.h"
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

	virtual void NativeDestruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|에셋")
	USP_TextButton* StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|에셋")
	USP_TextButton* LoadButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|에셋")
	USP_TextButton* OptionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|에셋")
	USP_TextButton* ExitButton;

	UFUNCTION()
	void GameStart();
	
	UFUNCTION()
	void LoadGame();
	
	UFUNCTION()
	void LoadOptionWidget();
	

};
