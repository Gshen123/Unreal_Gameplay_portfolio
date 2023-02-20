// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "Gameplay_Portfolio/Camera/SP_PlayerCameraManager.h"
#include "SP_BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_BasePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    FORCEINLINE ASP_PlayerCameraManager* GetCameraManager() const {return Cast<ASP_PlayerCameraManager>(PlayerCameraManager);}

protected:
    ASP_BasePlayerController(const FObjectInitializer& ObjectInitializer);

    UFUNCTION()
    void PopWidgetStack();
  
    UPROPERTY()
    EGameModeType Type = EGameModeType::None;

    UPROPERTY()
    UUserWidget* PopWidget = nullptr;
};
