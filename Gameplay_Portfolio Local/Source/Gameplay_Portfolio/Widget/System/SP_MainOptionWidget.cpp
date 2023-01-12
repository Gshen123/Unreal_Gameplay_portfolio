// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_MainOptionWidget.h"
#include "GameFramework/GameUserSettings.h"

const FString USP_MainOptionWidget::SCREENMODE_FULL = TEXT("  Full Screen  ");
const FString USP_MainOptionWidget::SCREENMODE_WINDOW = TEXT(" Window Mode ");
const FString USP_MainOptionWidget::RESOLUTION_SD = TEXT(" 720 X 480 ");
const FString USP_MainOptionWidget::RESOLUTION_HD = TEXT(" 1280 X 720 ");
const FString USP_MainOptionWidget::RESOLUTION_FHD = TEXT(" 1920 X 1080 ");
const FString USP_MainOptionWidget::RESOLUTION_QHD = TEXT(" 2560 X 1440 ");
const FString USP_MainOptionWidget::RESOLUTION_UHD = TEXT(" 3840 X 2160 ");
const FString USP_MainOptionWidget::VIEWDISTANCE_LOW = TEXT("     낮음     ");
const FString USP_MainOptionWidget::VIEWDISTANCE_MID = TEXT("     보통     ");
const FString USP_MainOptionWidget::VIEWDISTANCE_HIGH = TEXT("     높음     ");
const FString USP_MainOptionWidget::VIEWDISTANCE_EPIC = TEXT("     최대     ");
const FString USP_MainOptionWidget::FPS_SETTING_30 = TEXT(" 30 FPS ");
const FString USP_MainOptionWidget::FPS_SETTING_60 = TEXT(" 60 FPS ");
const FString USP_MainOptionWidget::FPS_SETTING_144 = TEXT(" 144 FPS ");
const FString USP_MainOptionWidget::FPS_SETTING_EPIC = TEXT(" 제한 없음  ");

void USP_MainOptionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USP_MainOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(GraphicTabBtn) GraphicTabBtn->MainButton->OnClicked.AddUniqueDynamic(this, &ThisClass::VisibleGraphicsOption);
	if(AudioTabBtn)  AudioTabBtn->MainButton->OnClicked.AddUniqueDynamic(this, &ThisClass::VisibleAudioOption);
	if(GameTabBtn) GameTabBtn->MainButton->OnClicked.AddUniqueDynamic(this, &ThisClass::VisibleGameOption);

	if(ScreenModeBoxString) ScreenModeBoxString->OnSelectionChanged.AddUniqueDynamic(this, &USP_MainOptionWidget::ChangeScreenMode);
	if(ScreenResolutionBoxString) ScreenResolutionBoxString->OnSelectionChanged.AddUniqueDynamic(this, &USP_MainOptionWidget::ChangeScreenResolution);
	if(ViewDistanceBoxString) ViewDistanceBoxString->OnSelectionChanged.AddUniqueDynamic(this, &USP_MainOptionWidget::ChangeViewDistance);
	if(FPSSetupBoxString) FPSSetupBoxString->OnSelectionChanged.AddUniqueDynamic(this, &USP_MainOptionWidget::ChangeFPS);

	if(VerticalSyncBtn) VerticalSyncBtn->OnClicked.AddUniqueDynamic(this, &USP_MainOptionWidget::ToggleVSyn);
	
	Settings = GEngine->GetGameUserSettings();

	if(ScreenModeBoxString) 
	{
		if(Settings->GetFullscreenMode() == EWindowMode::Fullscreen || EWindowMode::WindowedFullscreen) { ScreenModeBoxString->SetSelectedOption(SCREENMODE_FULL);}
		if(Settings->GetFullscreenMode() == EWindowMode::Windowed || EWindowMode::NumWindowModes) { ScreenModeBoxString->SetSelectedOption(SCREENMODE_WINDOW);}
	}

	if(ScreenResolutionBoxString)
	{
		if(Settings->GetScreenResolution() == FIntPoint(720, 480)) {ScreenResolutionBoxString->SetSelectedOption(RESOLUTION_SD);}
		if(Settings->GetScreenResolution() == FIntPoint(1280, 720)) {ScreenResolutionBoxString->SetSelectedOption(RESOLUTION_HD);}
		if(Settings->GetScreenResolution() == FIntPoint(1920, 1080)) {ScreenResolutionBoxString->SetSelectedOption(RESOLUTION_FHD);}
		if(Settings->GetScreenResolution() == FIntPoint(2560, 1440)) {ScreenResolutionBoxString->SetSelectedOption(RESOLUTION_QHD);}
		if(Settings->GetScreenResolution() == FIntPoint(3840, 2160)) {ScreenResolutionBoxString->SetSelectedOption(RESOLUTION_UHD);}
	}

	if(ViewDistanceBoxString)
	{
		if(Settings->GetViewDistanceQuality() == 100) {ViewDistanceBoxString->SetSelectedOption(VIEWDISTANCE_LOW);}
		if(Settings->GetViewDistanceQuality() == 200) {ViewDistanceBoxString->SetSelectedOption(VIEWDISTANCE_MID);}
		if(Settings->GetViewDistanceQuality() == 300) {ViewDistanceBoxString->SetSelectedOption(VIEWDISTANCE_HIGH);}
		if(Settings->GetViewDistanceQuality() == 400) {ViewDistanceBoxString->SetSelectedOption(VIEWDISTANCE_EPIC);}
	}

	if(FPSSetupBoxString)
	{
		if(Settings->GetFrameRateLimit() == 30) {FPSSetupBoxString->SetSelectedOption(FPS_SETTING_30);}
		if(Settings->GetFrameRateLimit() == 60) {FPSSetupBoxString->SetSelectedOption(FPS_SETTING_60);}
		if(Settings->GetFrameRateLimit() == 144) {FPSSetupBoxString->SetSelectedOption(FPS_SETTING_144);}
		if(Settings->GetFrameRateLimit() == 1000) {FPSSetupBoxString->SetSelectedOption(FPS_SETTING_EPIC);}
	}

	if(VerticalSyncBtn)
	{
		if(Settings->IsVSyncEnabled())
		{
			VerticalSyncBtn->WidgetStyle.Normal.TintColor = FLinearColor(0.496933,0.194618,0.356400,1.000000);
			auto box = Cast<UTextBlock>(VerticalSyncBtn->GetChildAt(0));
			FText content = FText::FromString("  On  ");
			box->SetText(content);
		}
		else
		{
			VerticalSyncBtn->WidgetStyle.Normal.TintColor = FLinearColor(0.260417,0.245917,0.240668,1.000000);
			auto box = Cast<UTextBlock>(VerticalSyncBtn->GetChildAt(0));
			FText content = FText::FromString("  Off  ");
			box->SetText(content);
		}
	}

}

void USP_MainOptionWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void USP_MainOptionWidget::VisibleGraphicsOption()
{
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void USP_MainOptionWidget::VisibleAudioOption()
{
	WidgetSwitcher->SetActiveWidgetIndex(1);
}

void USP_MainOptionWidget::VisibleGameOption()
{
	WidgetSwitcher->SetActiveWidgetIndex(2);
}

void USP_MainOptionWidget::ChangeScreenMode(FString string, ESelectInfo::Type type)
{
	if(string == SCREENMODE_FULL)
	{
		Settings->SetFullscreenMode(Settings->GetPreferredFullscreenMode());
	}
	else if(string == SCREENMODE_WINDOW)
	{
		Settings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		Settings->ApplyResolutionSettings(false);
		Settings->SetFullscreenMode(EWindowMode::Windowed);
	}

	if(Settings->IsFullscreenModeDirty())
	{
		Settings->ApplyResolutionSettings(false);
		Settings->SaveSettings();
	}

}

void USP_MainOptionWidget::ChangeScreenResolution(FString string, ESelectInfo::Type type)
{
	FIntPoint ip;
	if(string == RESOLUTION_SD) { ip = (720, 480); }
	else if(string == RESOLUTION_HD) { ip = (1280, 720); }
	else if(string == RESOLUTION_FHD) { ip = (1920, 1080); }
	else if(string == RESOLUTION_QHD) { ip = (2560, 1440); }
	else { ip = (3840, 2160); }
	Settings->SetScreenResolution(ip);
	
	if(Settings->IsScreenResolutionDirty())
	{
		Settings->ApplyResolutionSettings(false);
		Settings->SaveSettings();
	}
}


void USP_MainOptionWidget::ChangeViewDistance(FString string, ESelectInfo::Type type)
{
	if(string == VIEWDISTANCE_LOW) 	Settings->SetViewDistanceQuality(100);
	if(string == VIEWDISTANCE_MID) 	Settings->SetViewDistanceQuality(200);
	if(string == VIEWDISTANCE_HIGH) Settings->SetViewDistanceQuality(300);
	if(string == VIEWDISTANCE_EPIC) Settings->SetViewDistanceQuality(400);

	Settings->ApplySettings(false);
}


void USP_MainOptionWidget::ChangeFPS(FString string, ESelectInfo::Type type)
{
	if(string == FPS_SETTING_30) Settings->SetFrameRateLimit(30);
	if(string == FPS_SETTING_60) Settings->SetFrameRateLimit(60);
	if(string == FPS_SETTING_144) Settings->SetFrameRateLimit(144);
	if(string == FPS_SETTING_EPIC) Settings->SetFrameRateLimit(1000);

	Settings->ApplySettings(false);
}

void USP_MainOptionWidget::ToggleVSyn()
{
	if(Settings->IsVSyncEnabled())
	{
		Settings->SetVSyncEnabled(false);
		VerticalSyncBtn->WidgetStyle.Normal.TintColor = FLinearColor(0.260417,0.245917,0.240668,1.000000);
		auto box = Cast<UTextBlock>(VerticalSyncBtn->GetChildAt(0));
		FText content = FText::FromString("  Off  ");
		box->SetText(content);
	}
	else
	{
		Settings->SetVSyncEnabled(true);
		VerticalSyncBtn->WidgetStyle.Normal.TintColor = FLinearColor(0.496933,0.194618,0.356400,1.000000);
		auto box = Cast<UTextBlock>(VerticalSyncBtn->GetChildAt(0));
		FText content = FText::FromString("  On  ");
		box->SetText(content);
	}

	Settings->ApplySettings(false);
}

void USP_MainOptionWidget::SetDynamicResolution()
{
	Settings->SetDynamicResolutionEnabled(true);
	Settings->ApplyNonResolutionSettings();
}
