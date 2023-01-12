// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_SettingOptionWidget.h"
#include "Gameplay_Portfolio/Settings/SP_GameSetting.h"
#include "Gameplay_Portfolio/Widget/SP_TextButton.h"

void USP_SettingOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(SettingDisplayName);
	check(SettingCurrentValue);
	check(PrevSettingButton);
	check(NextSettingButton);

	NextSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnNextSetting);
	PrevSettingButton->OnClicked.AddDynamic(this, &ThisClass::OnPrevSetting);
}

void USP_SettingOptionWidget::Init(USP_GameSetting* InSetting)
{
	Setting = MakeWeakObjectPtr(InSetting);
	check(Setting.IsValid());

	UpdateTexts();
}

void USP_SettingOptionWidget::UpdateTexts() const
{
	if(Setting.IsValid())
	{
		//SettingDisplayName->Text_Context = FText::FromString(Setting->GetName());
		SettingDisplayName->SetText(Setting->GetName());
		SettingCurrentValue->SetText(Setting->GetCurrentOption().Name);
	}
}

void USP_SettingOptionWidget::OnNextSetting()
{
	if(Setting.IsValid())
	{
		Setting->ApplyNextOption();
		SettingCurrentValue->SetText(Setting->GetCurrentOption().Name);
	}
}

void USP_SettingOptionWidget::OnPrevSetting()
{
	if(Setting.IsValid())
	{
		Setting->ApplyPrevOption();
		SettingCurrentValue->SetText(Setting->GetCurrentOption().Name);
	}
}
