// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/ComboBoxString.h"
#include "Components/WidgetSwitcher.h"
#include "Gameplay_Portfolio/Widget/SP_TextButton.h"
#include "SP_MainOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_MainOptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta = (BindWidget))
	USP_TextButton* GraphicTabBtn;
	
	UPROPERTY(meta = (BindWidget))
	USP_TextButton* AudioTabBtn;
    	
	UPROPERTY(meta = (BindWidget))
	USP_TextButton* GameTabBtn;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|위젯|그래픽")
	UComboBoxString* ScreenModeBoxString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|위젯|그래픽")
	UComboBoxString* ScreenResolutionBoxString;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|위젯|그래픽")
	UComboBoxString* ViewDistanceBoxString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|위젯|그래픽")
	UComboBoxString* FPSSetupBoxString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "기본|위젯|그래픽")
	UButton* VerticalSyncBtn;
	
	UFUNCTION()
	void VisibleGraphicsOption();

	UFUNCTION()
	void VisibleAudioOption();

	UFUNCTION()
	void VisibleGameOption();

	UFUNCTION()
	void ChangeScreenMode(FString string, ESelectInfo::Type type);

	UFUNCTION()
	void ChangeScreenResolution(FString string, ESelectInfo::Type type);

	UFUNCTION()
	void ChangeViewDistance(FString string, ESelectInfo::Type type);

	UFUNCTION()
	void ChangeFPS(FString string, ESelectInfo::Type type);

	UFUNCTION()
	void ToggleVSyn();

	UFUNCTION()
	void SetDynamicResolution();

	static const FString SCREENMODE_FULL;
	static const FString SCREENMODE_WINDOW;
	static const FString RESOLUTION_SD;
	static const FString RESOLUTION_HD;
	static const FString RESOLUTION_FHD;
	static const FString RESOLUTION_QHD;
	static const FString RESOLUTION_UHD;
	static const FString VIEWDISTANCE_LOW;
	static const FString VIEWDISTANCE_MID;
	static const FString VIEWDISTANCE_HIGH;
	static const FString VIEWDISTANCE_EPIC;
	static const FString FPS_SETTING_30;
	static const FString FPS_SETTING_60;
	static const FString FPS_SETTING_144;
	static const FString FPS_SETTING_EPIC;

private:
	UGameUserSettings* Settings;
};
