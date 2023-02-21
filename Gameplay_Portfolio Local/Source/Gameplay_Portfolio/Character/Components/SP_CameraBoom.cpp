// Scope Portfolio. All rights reserved


#include "SP_CameraBoom.h"


void USP_CameraBoom::BeginPlay()
{
    Super::BeginPlay();
    
    SetCamMoveMode(ESP_CameraMode::Normal);
}

void USP_CameraBoom::CameraZoom(float Value)
{
    const float MultiValue = Value * ZoomMultiple;
    TargetArmLength += MultiValue;
    
    if(TargetArmLength < ZoomMinValue) TargetArmLength = ZoomMinValue;
    if(TargetArmLength > ZoomMaxValue) TargetArmLength = ZoomMaxValue;
}

void USP_CameraBoom::SetCamMoveMode(ESP_CameraMode NewCamMoveMode)
{
    check(NewCamMoveMode != ESP_CameraMode::None);
    if(CamMoveMode == NewCamMoveMode) return;
    
    if(NewCamMoveMode == ESP_CameraMode::CharacterSetting)
    {
        ZoomMinValue = 60.f;
        ZoomMaxValue = 320.f;
        ZoomMultiple = 16.f;
    }

    if(NewCamMoveMode == ESP_CameraMode::Normal)
    {
        ZoomMinValue = 160.f;
        ZoomMaxValue = 450.f;
        ZoomMultiple = 27.f;
    }
}
