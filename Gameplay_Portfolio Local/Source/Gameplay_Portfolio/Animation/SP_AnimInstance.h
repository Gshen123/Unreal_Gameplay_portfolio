// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_PlayerCharacter.h"
#include "SP_AnimInstance.generated.h"

//참고 레퍼런스
// https://aym0011.wordpress.com/tag/ue4/
// https://darkcatgame.tistory.com/23?category=813793

#define LEFT_FOOT_SOCK_NAME (FName(TEXT("foot_l")))
#define RIGHT_FOOT_SOCK_NAME (FName(TEXT("foot_r")))
#define IK_FOOT_ROOT_SOCK_NAME (FName(TEXT("foot_root")))
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_AnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK")
    bool bDebugIK = true;
    
protected:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
    ASP_PlayerCharacter* Character;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
    float GroundSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
    bool bIsMoving;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Locomotion")
    bool bIsInAir;

private:
    void FootIK(float DeltaTime);

    TTuple<bool, float, FVector> FootLineTrace(FName SocketName) const;

    static FRotator IK_NormalToRotator(FVector Vector);

    void IK_UpdateFootRotation(float DeltaTime, FRotator TargetValue, FRotator* FootRotatorValue) const;
    // Hip Offset
    void IK_UpdateCapsuleHalfHeight(float DeltaTime, float HipsShifts, bool bResetDefault) const;

    void IK_UpdateFootOffset(float DeltaTime, float TargetValue, float* EffectorValue) const;


    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK|Foot", meta = (AllowPrivateAccess = "true"))
    float CapsuleHalfHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK|Foot", meta = (AllowPrivateAccess = "true"))
    float TraceDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK|Foot", meta = (AllowPrivateAccess = "true"))
    float IKInterpSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK|Foot", meta = (AllowPrivateAccess = "true"))
    float DefaultOffset =5.0f;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK|Foot", meta = (AllowPrivateAccess = "true"))
    FRotator FootRot_R;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK|Foot", meta = (AllowPrivateAccess = "true"))
    FRotator FootRot_L;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK|Foot", meta = (AllowPrivateAccess = "true"))
    float  FootIK_R;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK|Foot", meta = (AllowPrivateAccess = "true"))
    float  FootIK_L;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK|Foot", meta = (AllowPrivateAccess = "true"))
    float  HipOffset;
    
    UPROPERTY()
    TArray<AActor*> IgnoreActors;
};