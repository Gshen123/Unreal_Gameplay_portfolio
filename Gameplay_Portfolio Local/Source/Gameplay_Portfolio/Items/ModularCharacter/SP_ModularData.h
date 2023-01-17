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

USTRUCT(BlueprintType)
struct FSP_DefaultItemData
{
    GENERATED_BODY()
    
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
};

UCLASS(Blueprintable, BlueprintType)
class USP_DefaultPartsAsset : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSP_DefaultItemData DefaultParts;
};


UENUM()
enum class EOccupiedParts : uint8
{
    None			 = 0         UMETA(Hidden),
    hasHead	             = (1 << 0)  UMETA(DisplayName = "머리"),
    hasTop               = (1 << 1)  UMETA(DisplayName = "상의"),
    hasBottom            = (1 << 2)  UMETA(DisplayName = "하의"),
    hasHandAndArm		 = (1 << 4)  UMETA(DisplayName = "팔"),
    hasFeetAndLeg	       = (1 << 5)  UMETA(DisplayName = "다리"),
    Max		       = (1 << 6)  UMETA(Hidden)
};

ENUM_CLASS_FLAGS(EOccupiedParts);

USTRUCT(BlueprintType)
struct FModularPartsSlotData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "머리", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Head"))
	TSoftObjectPtr<USP_ModularItemBase> Head = nullptr;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "상의", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Head"))
	TSoftObjectPtr<USP_ModularItemBase> Top = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "하의", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Head"))
	TSoftObjectPtr<USP_ModularItemBase> Bottom = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "팔", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Head"))
	TSoftObjectPtr<USP_ModularItemBase> Arm = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "다리", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Head"))
	TSoftObjectPtr<USP_ModularItemBase> Leg = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "전신 슈트", meta = (AllowedClasses = "/Script/Gameplay_Portfolio.SP_ItemModule_Head"))
	TSoftObjectPtr<USP_ModularItemBase> Suit = nullptr;
};