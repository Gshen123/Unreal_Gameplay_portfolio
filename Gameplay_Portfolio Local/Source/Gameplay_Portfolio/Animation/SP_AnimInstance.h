// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_FootIKManager.h"
#include "SP_PlayerCharacter.h"
#include "SP_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_AnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    USP_AnimInstance();

protected:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Locomotion")
    ASP_PlayerCharacter* Owner;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Locomotion")
    EGaitType Gait;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Locomotion")
    float GroundSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Locomotion")
    bool bIsMoving;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Locomotion")
    bool bIsInAir;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Locomotion")
    bool bPressedSprint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FookIK")
    FSP_FootIKInfo FootIKInfo;

private:
    TUniquePtr<FSP_FootIKManager> FootIKManager;
};