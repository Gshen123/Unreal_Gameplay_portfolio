// Scope Portfolio. All rights reserved


#include "SP_ModularGameMode.h"

ASP_ModularGameMode::ASP_ModularGameMode()
{
    CurrentGameMode = EGameModeType::CharacterSetup;
}

void ASP_ModularGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}
