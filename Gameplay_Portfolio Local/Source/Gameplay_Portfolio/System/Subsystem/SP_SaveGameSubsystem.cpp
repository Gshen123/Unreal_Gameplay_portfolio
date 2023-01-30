// Scope Portfolio. All rights reserved


#include "SP_SaveGameSubsystem.h"

#include "EngineUtils.h"
#include "SP_PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"

void USP_SaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void USP_SaveGameSubsystem::HandleStartingNewPlayer(const AController* NewPlayer) const
{
    ASP_PlayerState* PS = NewPlayer->GetPlayerState<ASP_PlayerState>();
    if (ensure(PS))
    {
        PS->LoadPlayerState(CurrentSaveGame);
    }
}

bool USP_SaveGameSubsystem::OverrideSpawnTransform(AController* NewPlayer)
{
    if (!IsValid(NewPlayer))
    {
        return false;
    }

    ASP_PlayerState* PS = NewPlayer->GetPlayerState<ASP_PlayerState>();
    if (PS == nullptr)
    {
        return false;
    }
    
    if (APawn* MyPawn = PS->GetPawn())
    {
        FPlayerSaveData* FoundData = CurrentSaveGame->GetPlayerData(PS);
        if (FoundData && FoundData->bResumeAtTransform)
        {		
            MyPawn->SetActorLocation(FoundData->Location);
            MyPawn->SetActorRotation(FoundData->Rotation);
            AController* PC = Cast<AController>(PS->GetOwner());
            
            // 카메라 및 컨트롤러의 방향도 설정합니다.
            PC->SetControlRotation(FoundData->Rotation);
            
            return true;
        }
    }
    
    return false;
}

void USP_SaveGameSubsystem::SetSlotName(FString NewSlotName)
{
    if (NewSlotName.Len() == 0)
    {
        return;
    }
    
    CurrentSlotName = NewSlotName;
}

void USP_SaveGameSubsystem::WriteSaveGame()
{
    USP_SaveGame SaveGame;
    
    AGameStateBase* GS = GetWorld()->GetGameState();
    if (GS == nullptr)
    {
        return;
    }
    
    // 멀티 플레이어별로 플레이어 정보를 저장합니다.
    for (int32 i = 0; i < GS->PlayerArray.Num(); i++)
    {
        ASP_PlayerState* PS = Cast<ASP_PlayerState>(GS->PlayerArray[i]);
        if (PS)
        {
            PS->SavePlayerState(CurrentSaveGame);
            break;
        }
    }
    
    // 월드에 존재하는 모든 액터를 순회합니다.
    for (FActorIterator It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        
        // 액터가 아니거나 특정 인터페이스를 상속받지 않은 액터는 저장목록에서 제외시킵니다.
        //if (!IsValid(Actor) || !Actor->Implements<USGameplayInterface>())
        //{
        //    continue;
        //}
        SaveGame.ActorSaver(Actor);
    }

    /// 게임 스테이트나 각종 저장할 오브젝트 유형을 저장합니다.
    /// SaveGame.ForLoopUObjectSaver(MyGameState.Objects)

    CurrentSaveGame = &SaveGame;
    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, CurrentSlotName, 0);
}

void USP_SaveGameSubsystem::LoadSaveGame(FString InSlotName /* = " "  */)
{
    //지정된 문자열이 있다면 슬롯명을 변경하고 아닌 경우, 기본 슬롯명을 유지합니다.
    SetSlotName(InSlotName);

    // 해당 슬롯에 저장된 게임이 존재하는지 확인합니다.
    if (UGameplayStatics::DoesSaveGameExist(CurrentSlotName, 0))
    {
        CurrentSaveGame = Cast<USP_SaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentSlotName, 0));
        if (CurrentSaveGame == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
            return;
        }

        UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame Data."));
        CurrentSaveGame->UObjectsPreloader(GetWorld()->GetGameState());
        CurrentSaveGame->UObjectDataLoader();
    }
    else
    {
        CurrentSaveGame = Cast<USP_SaveGame>(UGameplayStatics::CreateSaveGameObject(USP_SaveGame::StaticClass()));
        UE_LOG(LogTemp, Log, TEXT("Created New SaveGame Data."));
    }
}
