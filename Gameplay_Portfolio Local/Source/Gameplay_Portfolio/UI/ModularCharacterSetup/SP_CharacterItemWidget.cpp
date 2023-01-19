﻿// Scope Portfolio. All rights reserved


#include "SP_CharacterItemWidget.h"

#include "SP_AssetManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacterItemWidget, All, All);

void USP_CharacterItemWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(NextItemButton) NextItemButton->OnClicked.AddDynamic(this, &ThisClass::OnNextItem);
    if(PrevItemButton) PrevItemButton->OnClicked.AddDynamic(this, &ThisClass::OnPrevItem);

    InitAssets();
}

void USP_CharacterItemWidget::InitAssets()
{
    USP_AssetManager& AssetManager = USP_AssetManager::Get();

    TArray<FPrimaryAssetId> AssetIDs;
    AssetManager.GetPrimaryAssetIdList(AssetType, AssetIDs);
    
    for(const FPrimaryAssetId ID : AssetIDs)
    {
        FAssetData AssetDataToParse;
        AssetManager.GetPrimaryAssetData(ID, AssetDataToParse);

        FString nameFilter = AssetDataToParse.GetAsset()->GetFName().ToString();
        const USP_ModularItemBase* Asset = CastChecked<USP_ModularItemBase>(AssetDataToParse.GetAsset());
        if(!nameFilter.Contains("Default"))
        {
            Assets.Add(Asset);
        }
        else
        {
            Assets.Insert(Asset,0);
        }
    }

    if(Assets.Num() < 1)
    {
        UE_LOG(LogCharacterItemWidget, Error, TEXT("%s is Empty Or Not Setting"), *AssetType.GetName().ToString());
        return;
    }
    
    if(Assets[0].Get() == nullptr)
    {
        CurrentItem = AssetManager.GetAsset(Assets[0]);
    }
    
    SetItem();

    for(auto Asset : Assets)
    {
        UE_LOG(LogCharacterItemWidget, Display, TEXT("%s : %s"), *AssetType.GetName().ToString(), *Asset.Get()->Data.DisplayName.ToString());
    }

}

void USP_CharacterItemWidget::UpdateTexts() const
{
    if(CurrentItem)
    {
        TextBlock->SetText( CurrentItem->GetDisplayName());
        TypeTextBlock->SetText(FText::FromString(AssetType.ToString()));
    }
}

void USP_CharacterItemWidget::OnNextItem()
{
    if(index < Assets.Num() - 1) index++;
    else index = 0;

    SetItem();
}

void USP_CharacterItemWidget::OnPrevItem()
{
    if(index > 0) index--;
    else index = Assets.Num() - 1;

    SetItem();
}

void USP_CharacterItemWidget::SetItem()
{
    if(Assets[index].Get() == nullptr)
    {
        USP_AssetManager& AssetManager = USP_AssetManager::Get();
        CurrentItem = AssetManager.GetAsset(Assets[index]);
    }
    else
    {
        CurrentItem = Assets[index].Get();
    }
    
    UpdateTexts();
}
