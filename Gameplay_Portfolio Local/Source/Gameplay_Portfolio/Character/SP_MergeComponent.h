// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularData.h"
#include "SP_PlayerState.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "SP_MergeComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEPLAY_PORTFOLIO_API USP_MergeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USP_MergeComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
    void UpdateMesh();
    
    ASP_PlayerState* GetPlayerState() const;
    
    USP_DefaultPartsAsset* GetDefaultParts() const;

    bool CheckWearStatus(int32 bitmask);

    void Unwear(int32 bitmask);
public:
    
    UPROPERTY()
    TArray<USkeletalMesh*> Meshes;

    UPROPERTY()
    USP_DefaultPartsAsset* DefaultPartAsset;

    UPROPERTY()
    FModularPartsSlotData ModularPartsSlot;
    
    UPROPERTY()
    int32 WearStatus = 0;
};
