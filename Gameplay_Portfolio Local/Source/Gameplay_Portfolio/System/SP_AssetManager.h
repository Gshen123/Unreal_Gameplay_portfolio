// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SP_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
    USP_AssetManager();

    // Returns the AssetManager singleton object.
    static USP_AssetManager& Get();

    // Returns the asset referenced by a TSoftObjectPtr.  This will synchronously load the asset if it's not already loaded.
    template<typename AssetType>
    static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

    static TArray<FPrimaryAssetType> GetModularAsset();

protected:
	
    static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);
    static bool ShouldLogAssetLoads();

    // Thread safe way of adding a loaded asset to keep in memory.
    void AddLoadedAsset(const UObject* Asset);

    virtual void StartInitialLoading() override;

private:
    // Assets loaded and tracked by the asset manager.
    UPROPERTY()
    TSet<const UObject*> LoadedAssets;
	
    // Used for a scope lock when modifying the list of load assets.
    FCriticalSection LoadedAssetsCritical;

public:
    static const FPrimaryAssetType Module_HeadType;
    static const FPrimaryAssetType Module_TopType;
    static const FPrimaryAssetType Module_FeetAndLegsType;
    static const FPrimaryAssetType Module_BottomType;
    static const FPrimaryAssetType Module_SuitType;
    static const FPrimaryAssetType Module_HandAndArmType;
};

template <typename AssetType>
AssetType* USP_AssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
    AssetType* LoadedAsset = nullptr;

    const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

    if (AssetPath.IsValid())
    {
        LoadedAsset = AssetPointer.Get();
        if (!LoadedAsset)
        {
            LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
            ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
        }

        if (LoadedAsset && bKeepInMemory)
        {
            // Added to loaded asset list.
            Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
        }
    }

    return LoadedAsset;
}