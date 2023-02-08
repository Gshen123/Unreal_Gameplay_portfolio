// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
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
    ASP_BasePlayerController(const FObjectInitializer& ObjectInitializer);

    FORCEINLINE ASP_PlayerCameraManager* GetCameraManager() const {return Cast<ASP_PlayerCameraManager>(PlayerCameraManager);}
};
