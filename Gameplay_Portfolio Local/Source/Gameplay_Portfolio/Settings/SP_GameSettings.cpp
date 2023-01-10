// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameSettings.h"

void USP_GameSettings::SetName(const FString& InName)
{
	Name = InName;
}

void USP_GameSettings::SetOptions(const TArray<FSettingOption>& InOptions)
{
	Options = InOptions;
}

FSettingOption USP_GameSettings::GetCurrentOption() const
{
	return Options[0];
}

FString USP_GameSettings::GetName() const
{
	return Name;
}
