// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_PlayerCameraManager.generated.h"


#define SCOPE_CAMERA_DEFAULT_FOV		(80.0f)
#define SCOPE_CAMERA_DEFAULT_PITCH_MIN	(-35.0f)
#define SCOPE_CAMERA_DEFAULT_PITCH_MAX	(10.0f)

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API ASP_PlayerCameraManager : public APlayerCameraManager
{
    GENERATED_BODY()

public:
    ASP_PlayerCameraManager(const FObjectInitializer& ObjectInitializer);

protected:

    virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};
