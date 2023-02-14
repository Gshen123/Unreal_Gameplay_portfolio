// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "SP_GameModeBase.h"
#include "SP_PlayGameModeBase.generated.h"

// 멀티플레이 로직이 덜 필요하여 GameMode가 아닌 GameModeBase를 통해 경량화했습니다.
UCLASS(minimalapi, BlueprintType, Blueprintable)
class ASP_PlayGameModeBase : public ASP_GameModeBase
{
    GENERATED_BODY()

public:
    ASP_PlayGameModeBase();

    virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};



