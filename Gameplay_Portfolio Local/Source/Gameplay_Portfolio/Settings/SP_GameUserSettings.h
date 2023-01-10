// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "SP_GameUserSettings.generated.h"

class USP_GameSettings;

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

	const TArray<USP_GameSettings*>& GetVideoSettings() const;

private:
	TArray<USP_GameSettings*> VideoSettings;
};
