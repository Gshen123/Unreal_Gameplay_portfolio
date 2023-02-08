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

USTRUCT(BlueprintType)
struct FModularPartsSlotData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "머리", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Head"))
    TSoftObjectPtr<USP_ModularItemBase> Head = nullptr;
    
    TArray<FName> HeadShare;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "몸통", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Body"))
    TSoftObjectPtr<USP_ModularItemBase> Body = nullptr;

    UPROPERTY()
    TArray<FName> BodyShare;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "팔", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Arm"))
    TSoftObjectPtr<USP_ModularItemBase> Arm = nullptr;

    UPROPERTY()
    TArray<FName> ArmShare;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "다리", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Leg"))
    TSoftObjectPtr<USP_ModularItemBase> Leg = nullptr;

    UPROPERTY()
    TArray<FName> LegShare;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "전신 슈트", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Suit"))
    TSoftObjectPtr<USP_ModularItemBase> Suit = nullptr;
    
};