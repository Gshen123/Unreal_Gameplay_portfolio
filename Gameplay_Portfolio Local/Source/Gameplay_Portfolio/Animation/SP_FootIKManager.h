// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_FootIKManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSP_FootIKInfo
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effector)
    float LeftFootOffset = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)
    float LeftFootIKAlpha = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effector)
    FRotator LeftFootAngle = FRotator(0.f, 0.f, 0.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
    float RightFootOffset = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)
    float RightFootIKAlpha = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Angle)
    FRotator RightFootAngle = FRotator(0.f, 0.f, 0.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effector)
    float ZOffset = 0.f;
};

class GAMEPLAY_PORTFOLIO_API FSP_FootIKManager
{
public:
    FSP_FootIKManager();
    virtual ~FSP_FootIKManager();
    
    FSP_FootIKInfo UpdateFootIKInfo(UWorld* World, ACharacter* Character, FSP_FootIKInfo CurrentFootIKInfo, float DeltaSeconds);

private:
    FSP_FootIKInfo CalculateFootIKInterpolation(float DeltaSeconds, FSP_FootIKInfo CurrentFootIKInfo, FSP_FootIKInfo DesiredFootIKInfo);

    const float TraceDistanceFromFoot;
};

#define LEFT_FOOT_SOCK_NAME (FName(TEXT("foot_l")))
#define RIGHT_FOOT_SOCK_NAME (FName(TEXT("foot_r")))
#define IK_FOOT_ROOT_SOCK_NAME (FName(TEXT("ik_foot_root")))