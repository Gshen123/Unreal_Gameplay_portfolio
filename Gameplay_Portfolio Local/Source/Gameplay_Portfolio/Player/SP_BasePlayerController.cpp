// Scope Portfolio. All rights reserved


#include "SP_BasePlayerController.h"

#include "SP_HUDBase.h"
#include "Gameplay_Portfolio/Camera/SP_PlayerCameraManager.h"
#include "Gameplay_Portfolio/EnhancedInput/SP_InputComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerControllerBase, All, All);

ASP_BasePlayerController::ASP_BasePlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PlayerCameraManagerClass = ASP_PlayerCameraManager::StaticClass();
    OverridePlayerInputClass = USP_InputComponent::StaticClass();
}

void ASP_BasePlayerController::PopWidgetStack()
{
    UE_LOG(LogPlayerControllerBase, Log, TEXT("Pop"));
    const auto HUD = Cast<ASP_HUDBase>(GetHUD());
    HUD->PopWidgetStack();
}