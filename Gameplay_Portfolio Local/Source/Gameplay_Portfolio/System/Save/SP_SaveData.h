// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularData.h"
#include "UObject/Object.h"
#include "SP_SaveData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSP_ObjectRecord
{
    GENERATED_BODY()

public:

    // class that this object is
    UPROPERTY(BlueprintReadWrite)
    UClass* Class;

    // save the outer used for object so they get loaded back in the correct hierachy
    UPROPERTY(BlueprintReadWrite)
    UObject* Outer;

    // save the outer used for object so they get loaded back in the correct hierachy
    UPROPERTY(BlueprintReadWrite)
    int32 OuterID;

    // if the outer is an actor otherwise will be UObject
    UPROPERTY(BlueprintReadWrite)
    bool bActor;

    // this is for loading only, store a pointer for the loaded object here so you can loop for the records later to de-serialize all the data
    UPROPERTY(BlueprintReadWrite)
    UObject* Self;

    // Name of the object
    UPROPERTY(BlueprintReadWrite)
    FName Name;

    // serialized data for all UProperties that are 'SaveGame' enabled
    //UPROPERTY(BlueprintReadWrite)
    TArray<uint8> Data;

    // Spawn location if it's an actor
    UPROPERTY(BlueprintReadWrite)
    FTransform Transform;

    FSP_ObjectRecord():
        OuterID(0), bActor(false)
    {
        Class = nullptr;
        Outer = nullptr;
        Self = nullptr;
    }
};

USTRUCT()
struct FMaterialData
{
    GENERATED_BODY()
public:
    UPROPERTY()
    UMaterialInstance* MaterialInstance = nullptr;

    UPROPERTY()
    TMap<FName, FLinearColor> ParamData;
};

USTRUCT()
struct FSaveMeshData
{
    GENERATED_BODY()
public:
    UPROPERTY()
    FModularPartsSlotData ModularPartsSlot;

    UPROPERTY()
    TMap<FPrimaryAssetType, FString> MeshItemData;

    UPROPERTY()
    TMap<FName, float> MorphTargetData;

    UPROPERTY()
    TMap<int32, FMaterialData> MaterialData;

    void Empty()
    {
        ModularPartsSlot.Empty();
        MeshItemData.Empty();
        MorphTargetData.Empty();
        MaterialData.Empty();
    }

    bool IsEmpty() const
    {
        if(ModularPartsSlot.IsEmpty() && MeshItemData.IsEmpty() && MorphTargetData.IsEmpty() && MaterialData.IsEmpty()) return true;
        return false;
    }

    void AddMaterialData(int32 Index, FName ParamName, FLinearColor Value, UMaterialInstance* MaterialInstance)
    {
        FMaterialData NewData;
        NewData.MaterialInstance = MaterialInstance;
        NewData.ParamData.Add(ParamName, Value);
        MaterialData.Add(Index, NewData);
    }
};

USTRUCT()
struct  FPlayerSaveData
{
    GENERATED_BODY ()

public:

    /* 단순화를 위해 FString으로 변환된 온라인 하위 시스템(예: Steam)에서 정의한 플레이어 ID   */ 
    UPROPERTY()
    FString PlayerID;

    UPROPERTY()
    int32 Credits = 0;

    UPROPERTY()
    FTimespan PlayTime;
    
    /* 최장 생존 시간 */
    UPROPERTY()
    float PersonalRecordTime = 0.f;

    /* 저장하는 동안 플레이어가 살아있는 경우 위치 */
    UPROPERTY()
    FVector Location = FVector::Zero();

    /* 저장하는 동안 플레이어가 살아있는 경우 방향 */ 
    UPROPERTY()
    FRotator Rotation= FRotator::ZeroRotator;

    /* 우리는 항상 위치를 복원하고 싶지는 않으며, 월드의 특정 리스폰 지점에서 플레이어를 재개할 수 있습니다. */
    UPROPERTY()
    bool bResumeAtTransform = false;

    UPROPERTY()
    FSaveMeshData PlayerMeshData;

    FString GetPlayTime() const
    {
        return FString::Printf(TEXT("%02d:%02d:%02d"), PlayTime.GetHours(), PlayTime.GetMinutes(), PlayTime.GetSeconds());
    }
};