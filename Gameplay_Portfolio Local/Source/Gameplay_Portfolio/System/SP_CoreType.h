// Fill out your copyright notice in the Description page of Project Settings.

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