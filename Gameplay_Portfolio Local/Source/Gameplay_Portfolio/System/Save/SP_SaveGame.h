// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_SaveData.h"
#include "GameFramework/SaveGame.h"
#include "SP_SaveGame.generated.h"

// 세이브 시스템은 아래의 레퍼런스들을 참고하여 제작했습니다.

// 언리얼 오브젝트 처리 : 공식문서 https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Objects/Optimizations/
// 언리얼 엔진 4 의 공식 프로젝트 ActionRPG
// 톰 루먼의 세이브 시스템 https://www.tomlooman.com/unreal-engine-cpp-save-system/
// 언리얼 커뮤니티의 타당한 세이브 시스템 구현 https://unrealcommunity.wiki/savegame-pointers-and-structs-8wlg0qms
//                  ''                       https://forums.unrealengine.com/t/what-is-the-best-way-to-handle-saving-loading-an-array-of-objects/281775/6


// 간단한 데이터의 저장 시스템은 일부 코드와 BP 등으로도 충분히 쉽게 구현가능하지만, 이를 확장해서 여러 변수에 적용하면 비효율적인 작업이 됩니다.
// 규모가 있는 프로젝트에 부합하는 세이브 시스템을 목표로 두고 구현했습니다.

/**
 *  버전별 세이브파일의 관리 및 호환을 위
 */
namespace ERPGSaveGameVersion
{
    enum type
    {
        // Initial version
        Initial,
        // Added Inventory
        AddedInventory,
        // Added ItemData to store count/level
        AddedItemData,

        // -----<new versions must be added before this line>-------------------------------------------------
        VersionPlusOne,
        LatestVersion = VersionPlusOne - 1
  };
}

UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_SaveGame : public USaveGame
{
    GENERATED_BODY()

public:

    UPROPERTY()
    TArray<FPlayerSaveData> PlayerSaveDatas;
    
    // 모든 오브젝트들의 정보를 보관하는 배열
    UPROPERTY()
    TArray<FSP_ObjectRecord> ObjectRecords;

    // 직렬화하기 전이나 로드 후에 임시로 객체를 로드하는데 필요한 Outer를 담은 배열
    UPROPERTY()
    TArray<UObject*> TempObjects;

    // 맵의 일부이거나 사전에 로드되어 TempObjects에 없는 Outer를 담은 배열
    UPROPERTY()
    TArray<UObject*> PersistentOuters;

public:

    // 플레이어의 고유 ID값을 가져옵니다. (멀티 플레이어용)
    FPlayerSaveData* GetPlayerData(APlayerState* PlayerState);

    //액터들을 순회하며 직렬화합니다.
    UFUNCTION(BlueprintCallable)
    void ForLoopActorSaver(TArray<AActor*> SaveActors);

    //액터를 직렬화하여 저장합니다.
    UFUNCTION(BlueprintCallable)
    void ActorSaver(AActor* SaveActor);

    //저장된 정보를 기반으로 액터를 사전에 생성시킵니다.
    UFUNCTION(BlueprintCallable)
    void ActorPreloader(AActor* WorldActor, FSP_ObjectRecord& ActorRecord);

    // UObject 타입을 순회하며 직렬화합니다.
    UFUNCTION(BlueprintCallable)
    void ForLoopUObjectSaver(TArray<UObject*> SaveObjects);

    // 오브젝트를 직렬화하여 저장합니다.
    UFUNCTION(BlueprintCallable)
    void UObjectSaver(UObject* SaveObject);

    //저장된 정보를 기반으로 오브젝트를 사전에 생성시킵니다.
    UFUNCTION(BlueprintCallable)
    void UObjectsPreloader(AActor* WorldActor);

    // load all data after all objects exist so all pointers will load
    UFUNCTION(BlueprintCallable)
    void UObjectDataLoader();

    // serialize the data
    UFUNCTION(BlueprintCallable)
    void SaveData(UObject* Object, UPARAM(ref) TArray<uint8>& Data);

    // de-serialize the data
    UFUNCTION(BlueprintCallable)
    void LoadData(UObject* Object, UPARAM(ref) TArray<uint8>& Data);
};