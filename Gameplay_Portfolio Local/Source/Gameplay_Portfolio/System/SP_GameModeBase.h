// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SP_GameModeBase.generated.h"

/**
 * 
 */
UCLASS(minimalapi, BlueprintType, Blueprintable)
class ASP_GameModeBase : public AGameModeBase
{
    GENERATED_BODY()
public:
    ASP_GameModeBase();

    virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
