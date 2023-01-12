// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "SP_GameUserSettings.generated.h"

class USP_GameSetting;

DECLARE_MULTICAST_DELEGATE(FOnSettingsUpdateDelegate);

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_GameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	USP_GameUserSettings();

	static USP_GameUserSettings* Get();

	const TArray<USP_GameSetting*>& GetVideoSettings() const;

	void RunBenchmark();

	FOnSettingsUpdateDelegate OnVideoSettingsUpdatedelegate;
	
private:
	UPROPERTY()
	TArray<USP_GameSetting*> VideoSettings;
};
