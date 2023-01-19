// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "SP_GameModeBase.h"
#include "SP_PlayGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameModeTypeChanged, EGameModeType);

// 멀티플레이 로직이 덜 필요하여 GameMode가 아닌 GameModeBase를 통해 경량화했습니다.
UCLASS(minimalapi, BlueprintType, Blueprintable)
class ASP_PlayGameModeBase : public ASP_GameModeBase
{
    GENERATED_BODY()

public:
    ASP_PlayGameModeBase();

    virtual void StartPlay() override;

    EGameModeType GetPrevMode() const;

    FOnGameModeTypeChanged OnGameModeStateChanged;

protected:
    bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    bool ClearPause() override;

private:
    EGameModeType GameModeState = EGameModeType::None;

    EGameModeType PrevGameMode = EGameModeType::MainMenu;

    void SetGameModeType(EGameModeType Tpye);
};



