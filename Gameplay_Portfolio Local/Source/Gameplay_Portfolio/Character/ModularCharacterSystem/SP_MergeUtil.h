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
    static void ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings, TArray<FSkelMeshMergeSectionMappingOroa>& OutSectionMappings);
	
    static void ToMergeParams(const TArray<FSkelMeshMergeUVTransformMappingOroa>& InUVTransformsPerMesh, TArray<FSkelMeshMergeMeshUVTransformsOroa>& OutUVTransformsPerMesh);
	
    static USkeletalMesh* MergeMeshes(const FSkeletalMeshMergeParamsOroa& Params);
};

