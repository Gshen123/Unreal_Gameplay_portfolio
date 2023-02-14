// Scope Portfolio. All rights reserved


#include "SP_SaveGameSubsystem.h"

#include "EngineUtils.h"
#include "SP_GameInstance.h"
#include "SP_PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"

constexpr int32 UserId = 0;
constexpr int32 UTC_HOUR_KOREA = 9;

void USP_SaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void USP_SaveGameSubsystem::Deinitialize()
{
    CurrentSlotName = nullptr;
    OnSaveGameSignature.Clear();
    OnLoadGameSignature.Clear();
    
    Super::Deinitialize();
}

void USP_SaveGameSubsystem::HandleStartingNewPlayer(const AController* NewPlayer, EGameModeType Mode) const
{
    ASP_PlayerState* PS = NewPlayer->GetPlayerState<ASP_PlayerState>();
    if (ensure(PS)) PS->LoadPlayerState(CurrentSaveGame, Mode);
}

bool USP_SaveGameSubsystem::OverrideSpawnTransform(AController* NewPlayer)
{
    if (!IsValid(NewPlayer) || !CurrentSaveGame) return false;

    ASP_PlayerState* PS = NewPlayer->GetPlayerState<ASP_PlayerState>();
    if (PS == nullptr) return false;
    
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
    if (NewSlotName.Len() == 0) return;
    CurrentSlotName = NewSlotName;
}

void USP_SaveGameSubsystem::WriteSaveGame(FString InSlotName, EGameModeType Type)
{
    SetSlotName(InSlotName);

    if (UGameplayStatics::DoesSaveGameExist(CurrentSlotName, UserId))
        UGameplayStatics::DeleteGameInSlot(CurrentSlotName, UserId);
    
    if(CurrentSaveGame == nullptr)
    {
        const auto NewSaveGame = UGameplayStatics::CreateSaveGameObject(USP_SaveGame::StaticClass());
        CurrentSaveGame = Cast<USP_SaveGame>(NewSaveGame);
    }

    // 저장 시점의 게임모드 타입을 저장합니다.
    CurrentSaveGame->SaveModeType = Type;
    
    // UTC 표준과 한국 시간과의 오차를 처리합니다.
    FDateTime UTCTime = FDateTime::UtcNow();
    CurrentSaveGame->DateTime = FDateTime(UTCTime.Validate() + FTimespan(0,0,0, UTC_HOUR_KOREA));
    
    // 멀티 플레이어 정보를 저장합니다.
    AGameStateBase* GS = GetWorld()->GetGameState();
    for (int32 i = 0; i < GS->PlayerArray.Num(); i++)
    {
        ASP_PlayerState* PS = Cast<ASP_PlayerState>(GS->PlayerArray[i]);
        if (PS)
        {
            PS->SavePlayerState(CurrentSaveGame, Type);
            break;
        }
    }
    
    if(Type == EGameModeType::InGame)
    {
        // 월드에 존재하는 모든 액터를 순회하여 저장합니다.
        for (FActorIterator It(GetWorld()); It; ++It)
        {
            AActor* Actor = *It;
        
            // 액터가 아니거나 특정 인터페이스를 상속받지 않은 액터는 저장목록에서 제외시킵니다.
            //if (!IsValid(Actor) || !Actor->Implements<USGameplayInterface>())
            //{
            //    continue;
            //}
            CurrentSaveGame->ActorSaver(Actor);
        }

        /// 게임 스테이트나 각종 저장할 오브젝트 유형을 저장합니다.
        /// SaveGame.ForLoopUObjectSaver(MyGameState.Objects)
    }
    
    if(UGameplayStatics::SaveGameToSlot(CurrentSaveGame, CurrentSlotName, UserId)) OnSaveGameSignature.Broadcast();
}

void USP_SaveGameSubsystem::DeleteSaveGame(FString InSlotName)
{
    SetSlotName(InSlotName);
    UGameplayStatics::DeleteGameInSlot(CurrentSlotName, UserId);
    CurrentSaveGame = nullptr;
}

USP_SaveGame* USP_SaveGameSubsystem::LoadSaveGame(FString InSlotName, EGameModeType Type, bool OpenLevel)
{
    //지정된 문자열이 있다면 슬롯명을 변경하고 아닌 경우, 기본 슬롯명을 유지합니다.
    SetSlotName(InSlotName);

    // 해당 슬롯에 저장된 게임이 존재하는지 확인합니다.
    if (UGameplayStatics::DoesSaveGameExist(CurrentSlotName, UserId))
    {
        CurrentSaveGame = Cast<USP_SaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentSlotName, UserId));
        if (CurrentSaveGame == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
            return nullptr;
        }

        UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame Data."));

        // 게임모드에 따라 데이터를 불러옵니다.
        if(Type == EGameModeType::InGame)
        {
            CurrentSaveGame->UObjectsPreloader(GetWorld()->GetGameState());
            CurrentSaveGame->UObjectDataLoader();
        }

        OnLoadGameSignature.Broadcast();
    }
    else CurrentSaveGame = nullptr;

    if(OpenLevel && CurrentSaveGame) Cast<USP_GameInstance>(GetGameInstance())->OpenLevel(GetWorld(), CurrentSaveGame->SaveModeType);
    return CurrentSaveGame;
}

USP_SaveGame* USP_SaveGameSubsystem::GetCurrentSaveGame() const
{
    return CurrentSaveGame;
}
