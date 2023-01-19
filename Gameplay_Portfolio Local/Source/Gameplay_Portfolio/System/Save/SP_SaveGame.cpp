// Scope Portfolio. All rights reserved


#include "SP_SaveGame.h"
#include "SP_SaveData.h"
#include "SP_SaveGameArchive.h"
#include "GameFramework/Actor.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSaveGame, All, All);

FPlayerSaveData* USP_SaveGame::GetPlayerData(APlayerState* PlayerState)
{
    if (PlayerState == nullptr)
    {
        return nullptr;
    }

    // PIE에서는 고유 ID를 제공하지 않기때문에 따로 처리하여 데이터를 가져옵니다.
    if (PlayerState->GetWorld()->IsPlayInEditor())
    {
        UE_LOG(LogTemp, Log, TEXT("PIE 모드이므로 플레이어 저장 정보의 첫번째 인덱스만 가져옵니다."));

        if (PlayerSaveDatas.IsValidIndex(0))
        {
            return &PlayerSaveDatas[0];
        }
        
        return nullptr;
    }

    // Steam이나 EOS 등에서 사용자 ID를 관리하는 방식에 보통 String을 자주 활용합니다.
    FString PlayerID = PlayerState->GetUniqueId().ToString();
    // 배열을 반복해 플레이어별로 ID 값을 대입합니다.
    return PlayerSaveDatas.FindByPredicate([&](const FPlayerSaveData& Data) { return Data.PlayerID == PlayerID; });
}

// 액터들의 정보를 직렬화합니다.
void USP_SaveGame::ForLoopActorSaver(TArray<AActor*> SaveActors)
{
    for (AActor* SaveActor : SaveActors)
    {
        ActorSaver(SaveActor);
    }
}

// ObjectRecords 배열에 액터의 정보를 추가합니다. 추가로 안전한 Outer를 확보하여 임시로 TempObjects에 보관합니다.
void USP_SaveGame::ActorSaver(AActor* SaveActor)
{
    int32 Index = ObjectRecords.Emplace();
    FSP_ObjectRecord& ObjectRecord = ObjectRecords[Index];

    ObjectRecord.Name = SaveActor->GetFName();
    ObjectRecord.Transform = SaveActor->GetTransform();
    ObjectRecord.Class = SaveActor->GetClass();
    ObjectRecord.bActor = true;

    SaveData(SaveActor, ObjectRecord.Data);

    this->TempObjects.Add(SaveActor);
    UE_LOG(LogSaveGame, Display, TEXT("Complete Save Actor %s"), *SaveActor->GetName())
    
}

// BeginPlay/Constructor가 호출되기 전에 사전에 액터의 정보를 불러와 스폰시킵니다. 추가로 안전한 Outer를 확보하여 임시로 TempObjects에 보관합니다.
void USP_SaveGame::ActorPreloader(AActor* WorldActor, FSP_ObjectRecord& ActorRecord)
{

    FActorSpawnParameters SpawnParams;
    SpawnParams.Name = ActorRecord.Name;

    // TODO: change this to SpawnActorDeferred so you can de-serialize and apply data before it calls constructor\BeginPlay
    AActor* NewActor = WorldActor->GetWorld()->SpawnActor<AActor>(ActorRecord.Class, ActorRecord.Transform, SpawnParams);
    //AActor* NewActor = WorldActor->GetWorld()->SpawnActorDeferred()
        
    // BUG? actor doesn't appear to load scale correctly using transform so I specifically apply the scale after loading
    NewActor->SetActorScale3D(ActorRecord.Transform.GetScale3D());

    // don't load now, load after all objects are preloaded
    //LoadData(LoadObject, ObjectRecord.Data);

    // add to temp array for lookup it another object using already loaded objects as outers (array gets cleared once all objects loaded)
    this->TempObjects.Add(NewActor);

    UE_LOG(LogSaveGame, Display, TEXT("Complete Load Actor %s"), *NewActor->GetPathName())
}

// UObject 타입들을 직렬화합니다.
void USP_SaveGame::ForLoopUObjectSaver(TArray<UObject*>  SaveObjects)
{
    for (UObject* SaveObject : SaveObjects)
    {
        UObjectSaver(SaveObject);
    }
}

// ObjectRecords 배열에 UObject 타입의 객체 정보를 추가합니다. 추가로 안전한 Outer를 확보하여 임시로 TempObjects에 보관합니다.
void USP_SaveGame::UObjectSaver(UObject* SaveObject)
{
    if (SaveObject == nullptr)
    {
        UE_LOG(LogSaveGame, Error, TEXT("Invalid Save Object!"))
        return;
    }

    if (SaveObject->HasAnyFlags(EObjectFlags::RF_Transient))
    {
        UE_LOG(LogSaveGame, Warning, TEXT("Saving RF_Transient object"))
        return;
    }

    if (SaveObject->IsA(AActor::StaticClass()))
    {
        ActorSaver(Cast<AActor>(SaveObject));
        return;
    }

    int32 Index = ObjectRecords.Emplace();
    FSP_ObjectRecord& ObjectRecord = ObjectRecords[Index];

    // 임시 저장된 Outer 배열에서 해당 오브젝트의 OuterId 값을 찾습니다.
    ObjectRecord.OuterID = TempObjects.Find(SaveObject->GetOuter());
    ObjectRecord.bActor = false;

    // Outer 포인터 정보 저장/검색에 사용자 지정 ID를 사용합니다.
    // * Outer가 퍼시스턴트 레벨에 존재할 경우 ID는 음수 값으로 설정 (즉, SaveGame에서 로드되지 않습니다.)
    // * -1이 이미 INDEX_NONE에 할당되어 있고 SaveGame에 로드된 개체에 0+가 사용되므로 음수 ID는 -2부터 시작합니다.
    if (ObjectRecord.OuterID == INDEX_NONE)
    {
        ObjectRecord.OuterID = PersistentOuters.Find(SaveObject->GetOuter());
        if (ObjectRecord.OuterID != INDEX_NONE)
        {
            ObjectRecord.OuterID = -(ObjectRecord.OuterID + 2);
        }
        else
        {
            int32 PerIndex = PersistentOuters.Add(SaveObject->GetOuter());
            ObjectRecord.OuterID = -(PerIndex + 2);
            UE_LOG(LogSaveGame, Display, TEXT("Save Outer %s"), *SaveObject->GetOuter()->GetPathName())
        }
    }

    ObjectRecord.Name = SaveObject->GetFName();
    ObjectRecord.Class = SaveObject->GetClass();

    SaveData(SaveObject, ObjectRecord.Data);

    this->TempObjects.Add(SaveObject);

    UE_LOG(LogSaveGame, Display, TEXT("Complete Save UObject %s"), *SaveObject->GetName())
}

//BeginPlay/Constructor가 호출되기 전에 사전에 오브젝트의 정보를 불러와 생성시킵니다.
void USP_SaveGame::UObjectsPreloader(AActor* WorldActor)
{
    UObject* LoadOuter = nullptr;

    for (FSP_ObjectRecord& ObjectRecord : ObjectRecords)
    {
        if (ObjectRecord.bActor == false)
        {
            if (ObjectRecord.OuterID != INDEX_NONE)
            {
                // TempObjects 또는 PersistentOuters 에 저장된 OuterID 값을 찾아냅니다.
                if (TempObjects.IsValidIndex(ObjectRecord.OuterID) == true)
                {
                    LoadOuter = TempObjects[ObjectRecord.OuterID];
                    if (LoadOuter == nullptr)
                    {
                        UE_LOG(LogSaveGame, Error, TEXT("Unable to find Outer for object (invalid array object)"));
                    }
                }
                else
                {
                    int32 NewIndex = FMath::Abs(ObjectRecord.OuterID) - 2;

                    if (PersistentOuters.IsValidIndex(NewIndex)) 
                    {
                        LoadOuter = PersistentOuters[NewIndex];
                    }
                    else 
                    {
                        UE_LOG(LogSaveGame, Error, TEXT("Unable to find Outer for object (invalid ID)"));
                    }   
                }
            }
            if (LoadOuter == nullptr)
            {
                UE_LOG(LogSaveGame, Error, TEXT("Unable to find Outer for object (no pointer)"));
                continue;
            }

            UObject* LoadObject = NewObject<UObject>(LoadOuter, ObjectRecord.Class, ObjectRecord.Name);
            
            if (LoadObject == nullptr) return;

            // don't load now, load after all objects are preloaded
            //LoadData(LoadObject, ObjectRecord.Data);

            // add to here to cycle through and keep a pointer temporarly to avoid garbage collection (not sure if required but to be safe)
            this->TempObjects.Add(LoadObject);

            UE_LOG(LogSaveGame, Display, TEXT("Complete Load UObject %s %d"), *LoadObject->GetPathName(), this->TempObjects.Num() - 1)
        }

        else
        {
            ActorPreloader(WorldActor, ObjectRecord);
        }
    }
}

void USP_SaveGame::UObjectDataLoader()
{
    for (int32 a = 0 ; ObjectRecords.IsValidIndex(a) ; a++)
    {
        // Load now after all objects are preloaded
        LoadData(TempObjects[a], ObjectRecords[a].Data);
    }
}

void USP_SaveGame::SaveData(UObject* Object, UPARAM(ref) TArray<uint8>& Data)
{
    if (Object == nullptr) return;

    FMemoryWriter MemoryWriter = FMemoryWriter(Data, true);
    FSP_SaveGameArchive MyArchive = FSP_SaveGameArchive(MemoryWriter);

    Object->Serialize(MyArchive);
}

void USP_SaveGame::LoadData(UObject* Object, UPARAM(ref) TArray<uint8>& Data)
{
    if (Object == nullptr) return;

    FMemoryReader MemoryReader(Data, true);

    FSP_SaveGameArchive Ar(MemoryReader);
    Object->Serialize(Ar);
}