// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/Widget/SP_TextButton.h"
#include "SP_VideoSettingsWidget.generated.h"

class UVerticalBox;
class USP_SettingOptionWidget;
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_VideoSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VideoSettingsContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<USP_SettingOptionWidget> SettingOptionWidgetClass;

	UPROPERTY(meta = (BindWidget))
	USP_TextButton* BenchmarkButton;
	
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

private:

	UFUNCTION()
	void OnBenchmark();

	void OnVideoSettingsUpdated();
};
