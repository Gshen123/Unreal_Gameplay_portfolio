// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_VideoSettingsWidget.h"
#include "SP_SettingOptionWidget.h"
#include "Components/VerticalBox.h"
#include "Gameplay_Portfolio/Settings/SP_GameUserSettings.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"

DEFINE_LOG_CATEGORY_STATIC(LogVideoSettingsWidget, All, All);

void USP_VideoSettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto* UserSettings = USP_GameUserSettings::Get();
	if(!UserSettings)
	{
		UE_LOG(LogVideoSettingsWidget, Error, TEXT("UserSettings widget is nullptr"));
		return;
	}

	UserSettings->LoadSettings();
	const auto VideoSettings = UserSettings->GetVideoSettings();

	check(VideoSettingsContainer);
	VideoSettingsContainer->ClearChildren();

	for(USP_GameSetting* const Setting: VideoSettings)
	{
		const auto SettingWidget = CreateWidget<USP_SettingOptionWidget>(this, SettingOptionWidgetClass);
		check(SettingWidget);
		SettingWidget->Init(Setting);
		SettingWidget->SetPadding(FMargin(0, 5.0, 0, 5));
		VideoSettingsContainer->AddChild(SettingWidget);
	}
	
	check(BenchmarkButton);
	UserSettings->OnVideoSettingsUpdatedelegate.AddUObject(this, &ThisClass::OnVideoSettingsUpdated);
}

void USP_VideoSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(BenchmarkButton);
	BenchmarkButton->OnClicked.AddDynamic(this, &ThisClass::OnBenchmark);
}

void USP_VideoSettingsWidget::OnBenchmark()
{
	if(auto* UserSettings = USP_GameUserSettings::Get()) UserSettings->RunBenchmark();
}

void USP_VideoSettingsWidget::OnVideoSettingsUpdated()
{
	if(!VideoSettingsContainer) return;

	for(auto* Widget : VideoSettingsContainer->GetAllChildren())
	{
	    if(auto* SettingOptionWidget = Cast<USP_SettingOptionWidget>(Widget)) SettingOptionWidget->UpdateTexts();
	}
}
