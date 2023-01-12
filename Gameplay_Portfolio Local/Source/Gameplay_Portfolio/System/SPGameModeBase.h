// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SPGameModeBase.generated.h"

// 멀티플레이 로직이 덜 필요하여 GameMode가 아닌 GameModeBase를 통해 경량화했습니다.
UCLASS(minimalapi, BlueprintType, Blueprintable)
class ASPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASPGameModeBase();
};



