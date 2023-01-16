// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SP_MergeStruct.h"
#include "SP_MergeUtil.generated.h"

UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_MergeUtil : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION()
    static void ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings, TArray<FSkelMeshMergeSectionMappingScope>& OutSectionMappings);
	
    static void ToMergeParams(const TArray<FSkelMeshMergeUVTransformMappingScope>& InUVTransformsPerMesh, TArray<FSkelMeshMergeMeshUVTransformsScope>& OutUVTransformsPerMesh);
	
    static USkeletalMesh* MergeMeshes(const FSkeletalMeshMergeParamsScope& Params);
};

