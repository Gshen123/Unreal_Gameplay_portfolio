// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameSetting.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPGameSetting, All, All);

void USP_GameSetting::SetName(const FText& InName)
{
	Name = InName;
}

void USP_GameSetting::SetOptions(const TArray<FSettingOption>& InOptions)
{
	Options = InOptions;
}

FSettingOption USP_GameSetting::GetCurrentOption() const
{
	const int32 CurrentValue = GetCurrentValue();
	const auto Option = Options.FindByPredicate([&](const auto& Opt) {return CurrentValue == Opt.Value;});
	if(!Option)
	{
		UE_LOG(LogSPGameSetting, Error, TEXT("Option doesn't exist"), *Name.ToString());
		return FSettingOption{};
	}
	
	return *Option;
}

FText USP_GameSetting::GetName() const
{
	return Name;
}

void USP_GameSetting::AddGetter(TFunction<int32()> Func)
{
	Getter = Func;
}

void USP_GameSetting::AddSetter(TFunction<void(int32)> Func)
{
	Setter = Func;
}

void USP_GameSetting::ApplyNextOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if(CurrentIndex == INDEX_NONE) return;

	const int32 NextIndex = (CurrentIndex + 1) % Options.Num();
	SetCurrentValue(Options[NextIndex].Value);
}

void USP_GameSetting::ApplyPrevOption()
{
	const int32 CurrentIndex = GetCurrentIndex();
	if(CurrentIndex == INDEX_NONE) return;

	const int32 PrevIndex = CurrentIndex == 0 ? Options.Num() -1 : CurrentIndex - 1;
	SetCurrentValue(Options[PrevIndex].Value);
}

int32 USP_GameSetting::GetCurrentValue() const
{
	if(!Getter)
	{
		UE_LOG(LogSPGameSetting, Error, TEXT("Getter func is not set for %s"), *Name.ToString());
		return INDEX_NONE;
	}
	return Getter();
}

void USP_GameSetting::SetCurrentValue(int32 Value)
{
	if(!Setter)
	{
		UE_LOG(LogSPGameSetting, Error, TEXT("Setter func is not set for %s"), *Name.ToString());
		return;
	}

	Setter(Value);
}

int32 USP_GameSetting::GetCurrentIndex() const
{
	const int32 CurrentValue = GetCurrentValue();
	return Options.IndexOfByPredicate([&](const auto& Opt){return CurrentValue == Opt.Value;});
}
