// Scope Portfolio. All rights reserved


#include "SP_GameModeBase.h"

#include "Subsystem/SP_SaveGameSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SPGameModeBase, All, All);
ASP_GameModeBase::ASP_GameModeBase()
{
}

EGameModeType ASP_GameModeBase::GetPrevMode() const
{
    return PrevGameMode;
}

// 플레이어로부터 게임에 참여할 준비가 되었다는 신호를 받으면서 호출됩니다.
void ASP_GameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    // Super가 호출되기 전에 게임스테이트의 정보를 갱신합니다.
    USP_SaveGameSubsystem* SG = GetGameInstance()->GetSubsystem<USP_SaveGameSubsystem>();
    SG->HandleStartingNewPlayer(NewPlayer, CurrentGameMode);

    Super::HandleStartingNewPlayer_Implementation(NewPlayer);

    // 지정된 스폰 위치를 검사하고 적용합니다.
    if(CurrentGameMode == EGameModeType::InGame) SG->OverrideSpawnTransform(NewPlayer);
}

void ASP_GameModeBase::SetGameModeType(EGameModeType GameModeType)
{
    if(CurrentGameMode == GameModeType) return;

    CurrentGameMode = GameModeType;
    if(CurrentGameMode != EGameModeType::None && CurrentGameMode != EGameModeType::Pause) PrevGameMode = GameModeType;
    OnGameModeStateChanged.Broadcast(GameModeType);
}

inline bool ASP_GameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if(PauseSet) SetGameModeType(EGameModeType::Pause);

    return PauseSet;
}

inline bool ASP_GameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();

    if(PauseCleared)
    {
        SetGameModeType(PrevGameMode);
        UE_LOG(Log_SPGameModeBase, Display, TEXT("PrevGameMode : %s"), *UEnum::GetValueAsString(PrevGameMode));
    }

    return PauseCleared;
}
