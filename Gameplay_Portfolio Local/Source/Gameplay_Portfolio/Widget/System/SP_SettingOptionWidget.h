// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SP_SettingOptionWidget.generated.h"

class UButton;
class USP_TextButton;
class USP_GameSetting;
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_SettingOptionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override; 
	
	UPROPERTY(meta = (BindWidget))
	USP_TextButton* SettingDisplayName;

	UPROPERTY(meta = (BindWidget))
	USP_TextButton* SettingCurrentValue;

	UPROPERTY(meta = (BindWidget))
	UButton* NextSettingButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PrevSettingButton;

private:
	TWeakObjectPtr<USP_GameSetting> Setting;

	void Init(USP_GameSetting* InSetting);
	void UpdateTexts() const;

	UFUNCTION()
	void OnNextSetting();

	UFUNCTION()
	void OnPrevSetting();

	friend class USP_VideoSettingsWidget;
};
