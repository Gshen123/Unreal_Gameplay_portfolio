﻿// Scope Portfolio. All rights reserved


#include "SP_GameModeBase.h"

#include "Subsystem/SP_SaveGameSubsystem.h"

ASP_GameModeBase::ASP_GameModeBase()
{
}


// 플레이어로부터 게임에 참여할 준비가 되었다는 신호를 받으면서 호출됩니다.
void ASP_GameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    // Super가 호출되기 전에 게임스테이트의 정보를 갱신합니다.
    USP_SaveGameSubsystem* SG = GetGameInstance()->GetSubsystem<USP_SaveGameSubsystem>();
    SG->HandleStartingNewPlayer(NewPlayer);

    Super::HandleStartingNewPlayer_Implementation(NewPlayer);

    // 지정된 스폰 위치를 검사하고 적용합니다.
    SG->OverrideSpawnTransform(NewPlayer);
}
