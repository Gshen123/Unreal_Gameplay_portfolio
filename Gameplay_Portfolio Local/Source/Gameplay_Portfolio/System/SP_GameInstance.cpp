// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_GameInstance.h"

#include "SP_AssetManager.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameInstance, All, All);

USP_DefaultPartsAsset* USP_GameInstance::GetDefaultMeshParts() const
{
    check(DefaultPartsAssets);
    
    if(DefaultPartsAssets.Get() == nullptr)
    {
        return USP_AssetManager::GetAsset(DefaultPartsAssets);
    }

    return DefaultPartsAssets.Get();
}
