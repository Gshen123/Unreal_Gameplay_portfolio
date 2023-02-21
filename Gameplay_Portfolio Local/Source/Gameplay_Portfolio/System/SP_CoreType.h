

#pragma once

#include "SP_CoreType.generated.h"

/**
 * 
 */

UENUM()
enum class EGameModeType : uint8
{
    None = 0,
    MainMenu = 1,
    CharacterSetup = 2,
    InGame = 3,
    Pause = 4,
    GameOver = 5,
    InGameUIMode = 6
};

// 타입별 사용자 정의된 메시 정보를 저장하고 불러오는 기능을 위해 사용됩니다.
UENUM()
enum class EMergePawnType : uint8
{
    None,
    Player   UMETA(DisplayName = "플레이어", Tooltip = "로컬 플레이어 커스텀 가능"),
    Peer     UMETA(DisplayName = "동료", Tooltip = "로컬 플레이어 커스텀 가능"),
    Pet      UMETA(DisplayName = "펫", Tooltip = "로컬 플레이어 커스텀 가능"),
    NPC1     UMETA(DisplayName = "NPC1", Tooltip = "서버만 접근가능"),
    NPC2     UMETA(DisplayName = "NPC2", Tooltip = "서버만 접근가능"),
};

USTRUCT(BlueprintType)
struct FLevelData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelDisplayName = NAME_None;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    UTexture2D* LevelThumb = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    EGameModeType Type = EGameModeType::None;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&);