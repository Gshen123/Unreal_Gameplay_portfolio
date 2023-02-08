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

void ASP_PlayerCameraManager::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
    check(Canvas);

    FDisplayDebugManager& DisplayDebugManager = Canvas->DisplayDebugManager;

    DisplayDebugManager.SetFont(GEngine->GetSmallFont());
    DisplayDebugManager.SetDrawColor(FColor::Yellow);
    DisplayDebugManager.DrawString(FString::Printf(TEXT("LyraPlayerCameraManager: %s"), *GetNameSafe(this)));

    Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);
}
