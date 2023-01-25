// Scope Portfolio. All rights reserved

#pragma once

#include "SP_ModularData.generated.h"

/**
 * 
 */
class USP_ModularItemBase;

UCLASS()
class USP_ModularData : public UObject
{
    GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class USP_DefaultPartsAsset : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "머리", Category = "Defaults")
    TSoftObjectPtr<USkeletalMesh> Head;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "몸체", Category = "Defaults" )
    TSoftObjectPtr<USkeletalMesh> Body;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "팔", Category = "Defaults" )
    TSoftObjectPtr<USkeletalMesh> Arm;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "다리", Category = "Defaults" )
    TSoftObjectPtr<USkeletalMesh> Leg;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "발", Category = "Defaults" )
    TSoftObjectPtr<USkeletalMesh> Feet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "손", Category = "Defaults" )
    TSoftObjectPtr<USkeletalMesh> Hand;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "스켈레톤", Category = "Defaults" )
    TSoftObjectPtr<USkeleton> Skeleton;
};


UENUM()
enum class EWearStatus : uint8
{
    None			 = 0         UMETA(Hidden),
    hasHead	             = (1 << 0)  UMETA(DisplayName = "머리"),
    hasBody              = (1 << 1)  UMETA(DisplayName = "몸통"),
    hasHandAndArm		 = (1 << 2)  UMETA(DisplayName = "팔"),
    hasFeetAndLeg	       = (1 << 3)  UMETA(DisplayName = "다리"),
    Max		       = (1 << 4)  UMETA(Hidden)
};

ENUM_CLASS_FLAGS(EWearStatus);

USTRUCT(BlueprintType)
struct FModularPartsSlotData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "머리", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Head"))
    TSoftObjectPtr<USP_ModularItemBase> Head = nullptr;

    UPROPERTY()
    int32 HeadShare = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "몸통", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Body"))
    TSoftObjectPtr<USP_ModularItemBase> Body = nullptr;

    UPROPERTY()
    int32 BodyShare = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "팔", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Arm"))
    TSoftObjectPtr<USP_ModularItemBase> Arm = nullptr;

    UPROPERTY()
    int32 ArmShare = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "다리", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Leg"))
    TSoftObjectPtr<USP_ModularItemBase> Leg = nullptr;

    UPROPERTY()
    int32 LegShare = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "전신 슈트", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Suit"))
    TSoftObjectPtr<USP_ModularItemBase> Suit = nullptr;
    
};