// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "Save/SP_SaveGame.h"
#include "SP_SaveGameSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveGameSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadGameSignature);
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_SaveGameSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    void HandleStartingNewPlayer(const AController* NewPlayer, EGameModeType Mode) const;

    UFUNCTION(BlueprintCallable)
    bool OverrideSpawnTransform(AController* NewPlayer);

    UFUNCTION(BlueprintCallable)
    void SetSlotName(FString NewSlotName);
    
    UFUNCTION(BlueprintCallable, Category = "SaveGame")
    void WriteSaveGame(FString InSlotName, EGameModeType Type = EGameModeType::None);

    UFUNCTION(BlueprintCallable)
    void DeleteSaveGame(FString InSlotName);

    /* Load from disk, optional slot name */
    USP_SaveGame* LoadSaveGame(FString InSlotName = "", bool OpenLevel = true, int LocalPlayerIndex = 0);

    USP_SaveGame* GetCurrentSaveGame() const;

    UPROPERTY()
    FOnSaveGameSignature OnSaveGameSignature;
    UPROPERTY()
    FOnLoadGameSignature OnLoadGameSignature;
    
protected:
    FString CurrentSlotName;

    UPROPERTY()
    USP_SaveGame* CurrentSaveGame;
};
