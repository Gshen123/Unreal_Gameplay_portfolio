﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_AssetManager.h"

USP_AssetManager::USP_AssetManager()
{
}

USP_AssetManager& USP_AssetManager::Get()
{
    check(GEngine);

    USP_AssetManager* OroaAssetManager = Cast<USP_AssetManager>(GEngine->AssetManager);
    return *OroaAssetManager;
}

void USP_AssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

    //GamePlayTagManager Init
}

UObject* USP_AssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
    if (AssetPath.IsValid())
    {
        if (ShouldLogAssetLoads())
        {
            TUniquePtr<FScopeLogTime> LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronously loaded asset [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
        }

        if (IsValid())
        {
            return GetStreamableManager().LoadSynchronous(AssetPath, false);
        }

        // Use LoadObject if asset manager isn't ready yet.
        return AssetPath.TryLoad();
    }

    return nullptr;
}

bool USP_AssetManager::ShouldLogAssetLoads()
{
    static bool bLogAssetLoads = FParse::Param(FCommandLine::Get(), TEXT("LogAssetLoads"));
    return bLogAssetLoads;
}

void USP_AssetManager::AddLoadedAsset(const UObject* Asset)
{
    if (ensureAlways(Asset))
    {
        FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
        LoadedAssets.Add(Asset);
    }
}