// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_PlayerCameraManager.generated.h"


#define SCOPE_CAMERA_DEFAULT_FOV		(80.0f)
#define SCOPE_CAMERA_DEFAULT_PITCH_MIN	(-89.0f)
#define SCOPE_CAMERA_DEFAULT_PITCH_MAX	(89.0f)

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

    virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
};
