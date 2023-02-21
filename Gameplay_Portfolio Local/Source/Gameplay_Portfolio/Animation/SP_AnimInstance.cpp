// Scope Portfolio. All rights reserved


#include "SP_AnimInstance.h"

#include "SP_PlayerCharacter.h"

USP_AnimInstance::USP_AnimInstance()
{
    FootIKManager = MakeUnique<FSP_FootIKManager>();
}

void USP_AnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if(const auto TempOwner = Cast<ASP_PlayerCharacter>(TryGetPawnOwner())) Owner = TempOwner;
    if(!Owner) UE_LOG(LogTemp, Error, TEXT("AnimError"));
}

void USP_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if(!Owner) UE_LOG(LogTemp, Error, TEXT("AnimError"));
    if(!Owner) return;

    const auto OwnerLocomotionInfo = Owner->GetLocomotionInfo();
    Gait = OwnerLocomotionInfo.Gait;
    GroundSpeed = OwnerLocomotionInfo.GroundSpeed;
    bIsMoving = OwnerLocomotionInfo.bIsMoving;
    bIsInAir = OwnerLocomotionInfo.bIsInAir;
    
    if(!bIsInAir && !bIsMoving)
        FootIKInfo = FootIKManager->UpdateFootIKInfo(GetWorld(), Owner, FootIKInfo, DeltaSeconds);
    else
    {
        const FSP_FootIKInfo EmptyFootIKInfo;
        FootIKInfo = EmptyFootIKInfo;
    }
}
