// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_MergeUtil.h"
#include "SkeletalMeshMerge.h"
#include "Engine/SkeletalMeshSocket.h"

void USP_MergeUtil::ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings,
                                   TArray<FSkelMeshMergeSectionMappingScope>& OutSectionMappings)
{
	if (InSectionMappings.Num() > 0)
	{
		OutSectionMappings.AddUninitialized(InSectionMappings.Num());
		for (int32 i = 0; i < InSectionMappings.Num(); ++i)
		{
			OutSectionMappings[i].SectionIDs = InSectionMappings[i].SectionIDs;
		}
	}
}

void USP_MergeUtil::ToMergeParams(const TArray<FSkelMeshMergeUVTransformMappingScope>& InUVTransformsPerMesh,
	TArray<FSkelMeshMergeMeshUVTransformsScope>& OutUVTransformsPerMesh)
{
	if (InUVTransformsPerMesh.Num() > 0)
	{
		OutUVTransformsPerMesh.Empty();
		OutUVTransformsPerMesh.AddUninitialized(InUVTransformsPerMesh.Num());
		for (int32 i = 0; i < InUVTransformsPerMesh.Num(); ++i)
		{
			TArray<FTransform>& OutUVTransforms = OutUVTransformsPerMesh[i].UVTransforms;
			const TArray<FSkelMeshMergeMeshUVTransformsScope>& InUVTransforms = InUVTransformsPerMesh[i].UVTransformsPerMesh;
			if (InUVTransforms.Num() > 0)
			{
				OutUVTransforms.Empty();
				OutUVTransforms.AddUninitialized(InUVTransforms.Num());
				for (int32 j = 0; j < InUVTransforms.Num(); j++)
				{
					OutUVTransforms[i] = InUVTransforms[i].UVTransforms[j];
				}
			}
		}
	}
}

USkeletalMesh* USP_MergeUtil::MergeMeshes(const FSkeletalMeshMergeParamsScope& Params)
{
	
	TArray<USkeletalMesh*> MeshesToMergeCopy = Params.MeshesToMerge;
	MeshesToMergeCopy.RemoveAll([](USkeletalMesh* InMesh)
	{
		return InMesh == nullptr;
	});
	if (MeshesToMergeCopy.Num() <= 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Must provide multiple valid Skeletal Meshes in order to perform a merge."));
		return nullptr;
	}
	EMeshBufferAccess BufferAccess = Params.bNeedsCpuAccess ? EMeshBufferAccess::ForceCPUAndGPU : EMeshBufferAccess::Default;
	TArray<FSkelMeshMergeSectionMappingScope> SectionMappings;
	TArray<FSkelMeshMergeMeshUVTransformsScope> UvTransforms;
	ToMergeParams(Params.MeshSectionMappings, SectionMappings);
	ToMergeParams(Params.UVTransformsPerMesh, UvTransforms);
	bool bRunDuplicateCheck = false;
	USkeletalMesh* BaseMesh = NewObject<USkeletalMesh>();
	if (Params.Skeleton && Params.bSkeletonBefore)
	{
		BaseMesh->SetSkeleton(Params.Skeleton);
		bRunDuplicateCheck = true;
		for (USkeletalMeshSocket* Socket : BaseMesh->GetMeshOnlySocketList())
		{
			if (Socket)
			{
				UE_LOG(LogTemp, Warning, TEXT("SkelMeshSocket: %s"), *(Socket->SocketName.ToString()));
			}
		}
		for (USkeletalMeshSocket* Socket : BaseMesh->GetSkeleton()->Sockets)
		{
			if (Socket)
			{
				UE_LOG(LogTemp, Warning, TEXT("SkelSocket: %s"), *(Socket->SocketName.ToString()));
			}
		}
	}

	TArray<FSkelMeshMergeSectionMapping> InForceSectionMapping;
	
	for(int i = 0; i <SectionMappings.Num(); i++)
	{
		FSkelMeshMergeSectionMapping s;
		s.SectionIDs = SectionMappings[i].SectionIDs;
		InForceSectionMapping.Add(s);
	}
	
	FSkelMeshMergeUVTransformMapping* InSectionUVTransforms = nullptr;

	for (int i = 0; i <UvTransforms.Num(); i++)
	{
		FSkelMeshMergeMeshUVTransforms s;
		s.UVTransforms = UvTransforms[i].UVTransforms;
		InSectionUVTransforms->UVTransformsPerMesh.Add(s);
	}
	
	FSkeletalMeshMerge Merger(BaseMesh, MeshesToMergeCopy, InForceSectionMapping, Params.StripTopLODS, BufferAccess, InSectionUVTransforms);
	if (!Merger.DoMerge())
	{
		UE_LOG(LogTemp, Warning, TEXT("Merge failed!"));
		return nullptr;
	}
	if (Params.Skeleton && !Params.bSkeletonBefore)
	{
		BaseMesh->SetSkeleton(Params.Skeleton);
	}
	if (bRunDuplicateCheck)
	{
		TArray<FName> SkelMeshSockets;
		TArray<FName> SkelSockets;
		for (USkeletalMeshSocket* Socket : BaseMesh->GetMeshOnlySocketList())
		{
			if (Socket)
			{
				SkelMeshSockets.Add(Socket->GetFName());
				UE_LOG(LogTemp, Warning, TEXT("SkelMeshSocket: %s"), *(Socket->SocketName.ToString()));
			}
		}
		for (USkeletalMeshSocket* Socket : BaseMesh->GetSkeleton()->Sockets)
		{
			if (Socket)
			{
				SkelSockets.Add(Socket->GetFName());
				UE_LOG(LogTemp, Warning, TEXT("SkelSocket: %s"), *(Socket->SocketName.ToString()));
			}
		}
		TSet<FName> UniqueSkelMeshSockets;
		TSet<FName> UniqueSkelSockets;
		UniqueSkelMeshSockets.Append(SkelMeshSockets);
		UniqueSkelSockets.Append(SkelSockets);
		int32 Total = SkelSockets.Num() + SkelMeshSockets.Num();
		int32 UniqueTotal = UniqueSkelMeshSockets.Num() + UniqueSkelSockets.Num();
		UE_LOG(LogTemp, Warning, TEXT("SkelMeshSocketCount: %d | SkelSocketCount: %d | Combined: %d"), SkelMeshSockets.Num(), SkelSockets.Num(), Total);
		UE_LOG(LogTemp, Warning, TEXT("SkelMeshSocketCount: %d | SkelSocketCount: %d | Combined: %d"), UniqueSkelMeshSockets.Num(), UniqueSkelSockets.Num(), UniqueTotal);
		UE_LOG(LogTemp, Warning, TEXT("Found Duplicates: %s"), *((Total != UniqueTotal) ? FString("True") : FString("False")));
	}
    
	return BaseMesh;

}
