// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SP_AnimType.generated.h"

/**
 * 
 */

// 애님 노티파이를 활용한 발자국 소리에 활용됩니다.
UENUM(BlueprintType)
enum class EStepType : uint8
{
    None UMETA(Hidden),
    Step ,
    WalkAndRun,
    Jump,
    Land,
};


// 플레이어 캐릭터로부터 애님 인스턴스가 필요한 정보들을 담고있습니다.
USTRUCT(BlueprintType)
struct FSP_LocomotionInfo
{
    GENERATED_BODY()

    FSP_LocomotionInfo() :
        GroundSpeed(0.f)
        , bIsMoving(false)
        , bIsInAir(false)
    {
    }
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GroundSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsMoving;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsInAir;
};