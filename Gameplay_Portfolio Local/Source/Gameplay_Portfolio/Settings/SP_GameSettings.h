// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SP_GameSettings.generated.h"

/**
 * 
 */

USTRUCT()
struct FSettingOption
{
	GENERATED_BODY()

	FString Name;

	int32 Value;
};

UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_GameSettings : public UObject
{
	GENERATED_BODY()

public:
	void SetName(const FString& InName);
	void SetOptions(const TArray<FSettingOption>& InOptions);

	FSettingOption GetCurrentOption() const;
	FString GetName() const;

private:
	FString Name;
	TArray<FSettingOption> Options;
};
