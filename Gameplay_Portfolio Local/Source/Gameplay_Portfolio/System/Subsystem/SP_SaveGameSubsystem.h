// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Save/SP_SaveGame.h"
#include "SP_SaveGameSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameSignature, class USP_SaveGame*, SaveObject);

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_SaveGameSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    void Initialize(FSubsystemCollectionBase& Collection) override;

    void HandleStartingNewPlayer(const AController* NewPlayer) const;

    UFUNCTION(BlueprintCallable)
    bool OverrideSpawnTransform(AController* NewPlayer);

    UFUNCTION(BlueprintCallable)
    void SetSlotName(FString NewSlotName);
	
    UFUNCTION(BlueprintCallable, Category = "SaveGame")
    void WriteSaveGame();

    /* Load from disk, optional slot name */
    void LoadSaveGame(FString InSlotName = "");

    UPROPERTY(BlueprintAssignable)
    FOnSaveGameSignature OnSaveGameLoaded;
    
protected:
    FString CurrentSlotName;

    UPROPERTY()
    USP_SaveGame* CurrentSaveGame;
};
