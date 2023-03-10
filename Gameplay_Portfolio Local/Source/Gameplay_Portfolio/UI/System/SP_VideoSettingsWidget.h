// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "SP_VideoSettingsWidget.generated.h"

class USP_TextButton;
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
	TSubclassOf<UUserWidget> SettingOptionWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UButton* BenchmarkButton;
	
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

private:

	UFUNCTION()
	void OnBenchmark();

	void OnVideoSettingsUpdated();
};
