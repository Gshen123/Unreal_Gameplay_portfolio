// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SPGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePauseDelegate, bool, IsPaused);

// 멀티플레이 로직을 위주로 설계된 프로젝트가 아니라서 GameMode가 아닌 GameModeBase를 통해 경량화했습니다.
UCLASS(minimalapi, BlueprintType, Blueprintable)
class ASPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASPGameModeBase();

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
	virtual bool ClearPause() override;

	UPROPERTY(BlueprintAssignable)
	FOnGamePauseDelegate OnGamePause;
};



