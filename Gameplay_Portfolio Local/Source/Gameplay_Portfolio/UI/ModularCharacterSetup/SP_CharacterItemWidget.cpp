// Scope Portfolio. All rights reserved


#include "SP_CharacterItemWidget.h"

#include "SP_AssetManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacterItemWidget, All, All);

void USP_CharacterItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(NextItemButton) NextItemButton->OnClicked.AddDynamic(this, &ThisClass::OnNextItem);
    if(PrevItemButton) NextItemButton->OnClicked.AddDynamic(this, &ThisClass::OnNextItem);
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
        const USP_ModularItemBase* Asset = CastChecked<USP_ModularItemBase>(AssetDataToParse.GetAsset());
        Assets.AddUnique(Asset);
    }

    if(Assets.Num() > 1)
    {
        UE_LOG(LogCharacterItemWidget, Error, TEXT("%s is Empty Or Not Setting"), AssetType.GetName());
    }

    if(Assets[0].Get() == nullptr)
    {
        CurrentItem = AssetManager.GetAsset(Assets[0]);
    }
    else
    {
        CurrentItem = Assets[0].Get();
    }
}

void USP_CharacterItemWidget::UpdateTexts() const
{
    if(CurrentItem)
    {
       TextBlock->SetText( CurrentItem->GetDisplayName());
    }
}

void USP_CharacterItemWidget::OnNextItem()
{
    
}

void USP_CharacterItemWidget::OnPrevItem()
{
    
}
