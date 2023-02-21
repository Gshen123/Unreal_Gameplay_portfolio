// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "SP_CameraBoom.generated.h"

UENUM(BlueprintType)
enum class ESP_CameraMode : uint8
{
    None              UMETA(Hidden),
    Normal            UMETA(DisplayName = "일반"),
    CharacterSetting  UMETA(DisplayName = "캐릭터 세팅"),
    Sprint            UMETA(DisplayName = "스프린트"),
};


UCLASS(BlueprintType, Blueprintable)
class GAMEPLAY_PORTFOLIO_API USP_CameraBoom : public USpringArmComponent
{
    GENERATED_BODY()

public:
    void CameraZoom(float Value);

    void SetCamMoveMode(ESP_CameraMode NewCamMoveMode);
    FORCEINLINE ESP_CameraMode GetCamMoveMode() const { return CamMoveMode; }
    
protected:
    virtual void BeginPlay() override;

private:
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
    ESP_CameraMode CamMoveMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta=(AllowPrivateAccess="true"))
    float ZoomMinValue = 60.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta=(AllowPrivateAccess="true"))
    float ZoomMaxValue = 320.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta=(AllowPrivateAccess="true"))
    float ZoomMultiple = 16.f;
};
