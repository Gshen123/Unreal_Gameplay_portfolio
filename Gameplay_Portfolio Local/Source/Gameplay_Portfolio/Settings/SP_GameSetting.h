﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SP_GameSetting.generated.h"

/**
 * 
 */


USTRUCT()
struct FSettingOption
{
	GENERATED_BODY()

	FText Name;

	int32 Value;
};


UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_GameSetting : public UObject
{
	GENERATED_BODY()

public:
	void SetName(const FText& InName);
	void SetOptions(const TArray<FSettingOption>& InOptions);

	FSettingOption GetCurrentOption() const;
	FText GetName() const;
	void AddGetter(TFunction<int32()> Func);
	void AddSetter(TFunction<void(int32)> Func);

	void ApplyNextOption();
	void ApplyPrevOption();

private:
	FText Name;
	TArray<FSettingOption> Options;
	TFunction<int32()> Getter;
	TFunction<void(int32)> Setter;
	
	int32 GetCurrentValue() const;
	void SetCurrentValue(int32 Value);
	int32 GetCurrentIndex() const;
};
