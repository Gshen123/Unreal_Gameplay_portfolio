// Scope Portfolio. All rights reserved


#include "SP_PlayerCameraManager.h"

#include "Engine/Canvas.h"

ASP_PlayerCameraManager::ASP_PlayerCameraManager(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    DefaultFOV = SCOPE_CAMERA_DEFAULT_FOV;
    ViewPitchMin = SCOPE_CAMERA_DEFAULT_PITCH_MIN;
    ViewPitchMax = SCOPE_CAMERA_DEFAULT_PITCH_MAX;
}

void ASP_PlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
    Super::UpdateViewTarget(OutVT, DeltaTime);
}
