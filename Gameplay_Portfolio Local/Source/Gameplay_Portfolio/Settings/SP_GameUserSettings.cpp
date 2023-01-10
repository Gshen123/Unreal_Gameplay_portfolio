// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameUserSettings.h"

#include "SP_GameSettings.h"

USP_GameUserSettings::USP_GameUserSettings()
{
	const TArray<FSettingOption> VFXOptions = {{"Low", 0}, {"Medium", 1}, {"High", 2}, {"Epic", 3}};

	{
		auto* Setting = NewObject<USP_GameSettings>();
		check(Setting);
		Setting->SetName("Anti-Aliasing");
		Setting->SetOptions(VFXOptions);
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<USP_GameSettings>();
		check(Setting);
		Setting->SetName("Textures");
		Setting->SetOptions(VFXOptions);
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<USP_GameSettings>();
		check(Setting);
		Setting->SetName("Global Illumination");
		Setting->SetOptions(VFXOptions);
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<USP_GameSettings>();
		check(Setting);
		Setting->SetName("Shadows");
		Setting->SetOptions(VFXOptions);
		VideoSettings.Add(Setting);
	}

	{
		auto* Setting = NewObject<USP_GameSettings>();
		check(Setting);
		Setting->SetName("Post Processing");
		Setting->SetOptions(VFXOptions);
		VideoSettings.Add(Setting);
	}
}

USP_GameUserSettings* USP_GameUserSettings::Get()
{
	return GEngine ? Cast<USP_GameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

const TArray<USP_GameSettings*>& USP_GameUserSettings::GetVideoSettings() const
{
	return VideoSettings;
}
