// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_HUDBase.h"
#include "SP_PlayerCharacter.h"
#include "Save/SP_SaveData.h"
#include "SP_ModularHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_ModularHUD : public ASP_HUDBase
{
    GENERATED_BODY()

public:
    FPlayerMeshData GetMeshData() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> CreateCharacterWidgetClass;
    
    virtual void BeginPlay() override;

};
