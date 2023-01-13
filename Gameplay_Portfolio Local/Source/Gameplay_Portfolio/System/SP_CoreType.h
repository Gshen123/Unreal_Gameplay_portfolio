// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SP_CoreType.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FLevelData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelDisplayName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    UTexture2D* LevelThumb;
};

UENUM()
enum class EGameModeType : uint8
{
    None = 0,
    MainMenu = 1,
    CharacterSetup = 2,
    InProgress = 3,
    Pause = 4,
    GameOver = 5,
};