// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "GameFramework/GameModeBase.h"
#include "Subsystem/SP_SaveGameSubsystem.h"
#include "SP_GameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameModeTypeChanged, EGameModeType);
/**
 * 
 */
UCLASS(minimalapi, BlueprintType, Blueprintable)
class ASP_GameModeBase : public AGameModeBase
{
    GENERATED_BODY()
public:
    ASP_GameModeBase();
    
    virtual EGameModeType GetPrevMode() const;
    
    FOnGameModeTypeChanged OnGameModeStateChanged;

protected:

    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    
    virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

    void SetGameModeType(EGameModeType GameModeType);

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    virtual bool ClearPause() override;
    
    UPROPERTY()
    EGameModeType CurrentGameMode = EGameModeType::None;
    UPROPERTY()
    EGameModeType PrevGameMode = EGameModeType::None;
private:

    USP_SaveGameSubsystem* GetSaveSubSystem() const;
};

