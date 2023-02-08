// Scope Portfolio. All rights reserved


#include "SP_BasePlayerController.h"
#include "Gameplay_Portfolio/Camera/SP_PlayerCameraManager.h"

ASP_BasePlayerController::ASP_BasePlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PlayerCameraManagerClass = ASP_PlayerCameraManager::StaticClass();
}
