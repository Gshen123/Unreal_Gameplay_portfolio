// Scope Portfolio. All rights reserved


#include "SP_AnimInstance.h"

#include "SP_PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


void USP_AnimInstance::NativeInitializeAnimation()
{
    if(!Character) Character = Cast<ASP_PlayerCharacter>(TryGetPawnOwner());
    if(!Character) return;

    CapsuleHalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    IgnoreActors.Add(Character);
}

void USP_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    if(!Character) return;

    const auto OwnerLocomotionInfo = Character->GetLocomotionInfo();
    GroundSpeed = OwnerLocomotionInfo.GroundSpeed;
    bIsMoving = OwnerLocomotionInfo.bIsMoving;
    bIsInAir = OwnerLocomotionInfo.bIsInAir;

    if(!bIsInAir) FootIK(DeltaSeconds);
}

void USP_AnimInstance::FootIK(float DeltaTime)
{
    TTuple<bool, float, FVector> Foot_R = FootLineTrace(RIGHT_FOOT_SOCK_NAME);
    TTuple<bool, float, FVector> Foot_L = FootLineTrace(LEFT_FOOT_SOCK_NAME);

    if(!bIsMoving)
    {
        IK_UpdateFootRotation(DeltaTime, IK_NormalToRotator(Foot_R.Get<2>()), &FootRot_R);
        IK_UpdateFootRotation(DeltaTime, IK_NormalToRotator(Foot_L.Get<2>()), &FootRot_L);
    }
    else
    {
        IK_UpdateFootRotation(DeltaTime, FRotator::ZeroRotator, &FootRot_R);
        IK_UpdateFootRotation(DeltaTime, FRotator::ZeroRotator, &FootRot_L);
    }

    // 힙 오프셋을 적용합니다.
    float TargetHipOffset = UKismetMathLibrary::Min(Foot_L.Get<1>(), Foot_R.Get<1>());
    if (TargetHipOffset > 0.0f) TargetHipOffset = 0.0f;
    IK_UpdateFootOffset(DeltaTime, TargetHipOffset, &HipOffset);
    IK_UpdateCapsuleHalfHeight(DeltaTime, TargetHipOffset, false);

    IK_UpdateFootOffset(DeltaTime,(Foot_R.Get<1>() - 110.f) / - 45.f, &FootIK_R);
    IK_UpdateFootOffset(DeltaTime,(Foot_L.Get<1>()  - 110.f) / - 45.f, &FootIK_L);
}

// 플레이어 기준 최상단 좌표에서 본의 위치까지 레이캐스트를 실행합니다.
TTuple<bool, float, FVector> USP_AnimInstance::FootLineTrace(FName SocketName) const
{
    const FVector SocketLocation = Character->GetMesh()->GetSocketLocation(SocketName);
    const FVector Start {SocketLocation.X, SocketLocation.Y, Character->GetActorLocation().Z};
    const FVector End {Start - FVector(0.f,0.f, CapsuleHalfHeight + TraceDistance)};

    FHitResult HitResult;
    EDrawDebugTrace::Type DebugType = EDrawDebugTrace::None;
    if(bDebugIK) DebugType = EDrawDebugTrace::ForOneFrame;
	
    UKismetSystemLibrary::LineTraceSingle(
          this,
          Start,
          End,
          ETraceTypeQuery::TraceTypeQuery1,
          false,
          IgnoreActors,
          DebugType,
          HitResult,
          false);

    float Offset; 
    if(HitResult.IsValidBlockingHit())
    {
        float ImpactLegth = (HitResult.ImpactPoint - HitResult.TraceEnd).Size();
        Offset = DefaultOffset + (ImpactLegth - TraceDistance);
    }
    else Offset = 0.0f;

    return MakeTuple(HitResult.IsValidBlockingHit(),Offset, HitResult.ImpactNormal);
}

FRotator USP_AnimInstance::IK_NormalToRotator(FVector Vector)
{
    float A = UKismetMathLibrary::DegAtan2(Vector.X, Vector.Z) * -1.0f;
    float B = UKismetMathLibrary::DegAtan2(Vector.Y, Vector.Z);
    const FRotator Result = FRotator(A, 0.0f, B);
 
    return Result;
}

void USP_AnimInstance::IK_UpdateFootRotation(float DeltaTime, FRotator TargetValue, FRotator* FootRotatorValue) const
{
    FRotator InterpRotator = UKismetMathLibrary::RInterpTo(*FootRotatorValue, TargetValue, DeltaTime, IKInterpSpeed);
    *FootRotatorValue = InterpRotator;
}

void USP_AnimInstance::IK_UpdateFootOffset(float DeltaTime, float TargetValue, float* EffectorValue) const
{
    float fInterpValue = UKismetMathLibrary::FInterpTo(*EffectorValue, TargetValue, DeltaTime, IKInterpSpeed);
    *EffectorValue = fInterpValue;
}

void USP_AnimInstance::IK_UpdateCapsuleHalfHeight(float DeltaTime, float HipsShifts, bool bResetDefault) const
{
    UCapsuleComponent* Capsule = Character->GetCapsuleComponent();
    if (Capsule == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("IK : Capsule is NULL"));
        return;
    }
    
    float CapsuleHalf;
    if (bResetDefault == true) CapsuleHalf = CapsuleHalfHeight;
    else CapsuleHalf = CapsuleHalfHeight - UKismetMathLibrary::Abs(HipsShifts) * 0.5f;
    
    float ScaledCapsuleHalfHeight = Capsule->GetScaledCapsuleHalfHeight();
    const float InterpValue = UKismetMathLibrary::FInterpTo(ScaledCapsuleHalfHeight, CapsuleHalf, DeltaTime, IKInterpSpeed);
 
    Capsule->SetCapsuleHalfHeight(InterpValue, true);
}
