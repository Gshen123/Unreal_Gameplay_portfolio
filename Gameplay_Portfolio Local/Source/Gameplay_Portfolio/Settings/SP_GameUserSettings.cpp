// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameUserSettings.h"
#include "SP_GameSetting.h"

#define BIND_SETTINGS_FUNC(Func)    \
	[&](int32 Level)			\
	{					\
		Func(Level);		\
		ApplySettings(false);	\
	}					\

//FTEXT 기반 현지화 적용
#define LOCTEXT_NAMESPACE "GameUserSettings"

USP_GameUserSettings::USP_GameUserSettings()
{
	const TArray<FSettingOption> VFXOptions =
	{
		{LOCTEXT("VFXQualityLow_Loc","Low"), 0},
		{LOCTEXT("VFXQualityMedium_Loc","Medium"), 1},
		{LOCTEXT("VFXQualityHigh_Loc","High"), 2},
		{LOCTEXT("VFXQualityEpic_Loc","Epic"), 3},
		{LOCTEXT("VFXQualityCinematic_Loc","Cinematic"), 4}
	};
	
	const TArray<FSettingOption> ResolutionOptions =
	{
		{LOCTEXT("720X480","720X480"), 0},
		{LOCTEXT("1200X720","1200X720"), 1},
		{LOCTEXT("1920X1080","1920X1080"), 2},
		{LOCTEXT("2560X1440","2560X1440"), 3},
		{LOCTEXT("3840X2160","3840X2160"), 4}
	};

	{
		auto* Setting = NewObject<USP_GameSetting>();
		check(Setting);
		Setting->SetName(LOCTEXT("AntiAliasing_LOC", "Anti-Aliasing"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() {return GetAntiAliasingQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetAntiAliasingQuality));
		VideoSettings.Add(Setting);
	}


	{
		auto* Setting = NewObject<USP_GameSetting>();
		check(Setting);
		Setting->SetName(LOCTEXT("Textures_LOC","Textures"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() {return GetTextureQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetTextureQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<USP_GameSetting>();
		check(Setting);
		Setting->SetName(LOCTEXT("Global Illumination_LOC","Global Illumination"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() {return GetGlobalIlluminationQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetGlobalIlluminationQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<USP_GameSetting>();
		check(Setting);
		Setting->SetName(LOCTEXT("Shadows_LOC","Shadows"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() {return GetShadowQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetShadowQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<USP_GameSetting>();
		check(Setting);
		Setting->SetName(LOCTEXT("Post Processing_LOC","Post Processing"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() {return GetPostProcessingQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetPostProcessingQuality));
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<USP_GameSetting>();
		check(Setting);
		Setting->SetName(LOCTEXT("Reflections_LOC","Reflections"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() {return GetReflectionQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetReflectionQuality));
		VideoSettings.Add(Setting);
	}
	
	{
		auto* Setting = NewObject<USP_GameSetting>();
		check(Setting);
		Setting->SetName(LOCTEXT("Effects_LOC","Effects"));
		Setting->SetOptions(VFXOptions);
		Setting->AddGetter([&]() {return GetVisualEffectQuality();});
		Setting->AddSetter(BIND_SETTINGS_FUNC(SetVisualEffectQuality));
		VideoSettings.Add(Setting);
	}

	
}

USP_GameUserSettings* USP_GameUserSettings::Get()
{
	return GEngine ? Cast<USP_GameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

const TArray<USP_GameSetting*>& USP_GameUserSettings::GetVideoSettings() const
{
	return VideoSettings;
}

void USP_GameUserSettings::RunBenchmark()
{
	RunHardwareBenchmark();
	ApplySettings(false);
	OnVideoSettingsUpdatedelegate.Broadcast();
}

#undef LOCTEXT_NAMESPACE