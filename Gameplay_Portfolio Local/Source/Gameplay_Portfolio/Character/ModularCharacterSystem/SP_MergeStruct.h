// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SP_MergeStruct.generated.h"

/**
 * 
 */
class GAMEPLAY_PORTFOLIO_API SP_MergeStruct
{
public:
	SP_MergeStruct();
	~SP_MergeStruct();
};

USTRUCT(BlueprintType)
struct GAMEPLAY_PORTFOLIO_API FSkelMeshMergeSectionMapping_BP
{
	GENERATED_BODY()
	/** Indices to final section entries of the merged skeletal mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Merge Params")
	TArray < int32 > SectionIDs;
};

USTRUCT(BlueprintType)
struct GAMEPLAY_PORTFOLIO_API FSkelMeshMergeSectionMappingOroa
{
	GENERATED_USTRUCT_BODY()
	
	/** indices to final section entries of the merged skel mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Merge Parameters")
	TArray<int32> SectionIDs;
};

USTRUCT(BlueprintType)
struct GAMEPLAY_PORTFOLIO_API FSkelMeshMergeMeshUVTransformsOroa
{
	GENERATED_USTRUCT_BODY()

	/** A list of how UVs should be transformed on a given mesh, where index represents a specific UV channel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Merge Parameters")
	TArray<FTransform> UVTransforms;
};

USTRUCT(BlueprintType)
struct GAMEPLAY_PORTFOLIO_API FSkelMeshMergeUVTransformMappingOroa
{
	GENERATED_USTRUCT_BODY()
	
	/** UV coordinates transform datam one entry for each Skeletal Mesh. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Merge Parameters")
	TArray<FSkelMeshMergeMeshUVTransformsOroa> UVTransformsPerMesh;
};

USTRUCT(BlueprintType)
struct GAMEPLAY_PORTFOLIO_API FSkeletalMeshMergeParamsOroa
{
	GENERATED_BODY()
	FSkeletalMeshMergeParamsOroa()
	{
		StripTopLODS = 0;
		bNeedsCpuAccess = false;
		bSkeletonBefore = false;
		Skeleton = nullptr;
	}
	// An optional array to map sections from the source meshes to merged section entries
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray < FSkelMeshMergeSectionMapping_BP > MeshSectionMappings;
	// An optional array to transform the UVs in each mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray < FSkelMeshMergeUVTransformMappingOroa > UVTransformsPerMesh;
	// The list of skeletal meshes to merge.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray < USkeletalMesh* > MeshesToMerge;
	// The number of high LODs to remove from input meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StripTopLODS;
	// Whether or not the resulting mesh needs to be accessed by the CPU for any reason (e.g. for spawning particle effects).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bNeedsCpuAccess : 1;
	// Update skeleton before merge. Otherwise, update after.
	// Skeleton must also be provided.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bSkeletonBefore : 1;
	// Skeleton that will be used for the merged mesh.
	// Leave empty if the generated skeleton is OK.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeleton* Skeleton;
};
