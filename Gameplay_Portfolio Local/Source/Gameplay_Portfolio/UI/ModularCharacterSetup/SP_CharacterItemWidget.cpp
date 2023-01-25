// Scope Portfolio. All rights reserved


#include "SP_CharacterItemWidget.h"

#include "SP_AssetManager.h"
#include "SP_PlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacterItemWidget, All, All);

void USP_CharacterItemWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(NextItemButton) NextItemButton->OnClicked.AddDynamic(this, &ThisClass::OnNextItem);
    if(PrevItemButton) PrevItemButton->OnClicked.AddDynamic(this, &ThisClass::OnPrevItem);
}

void USP_CharacterItemWidget::Init()
{
    USP_AssetManager& AssetManager = USP_AssetManager::Get();
    
    TArray<FPrimaryAssetId> AssetIDs; 
    AssetManager.GetPrimaryAssetIdList(AssetType, AssetIDs);

    for(const FPrimaryAssetId ID : AssetIDs)
    {
        FAssetData AssetDataToParse;
        AssetManager.GetPrimaryAssetData(ID, AssetDataToParse);
        auto NameFilter = AssetDataToParse.AssetName.ToString();
        if(NameFilter != "Default")
        {
            if(const USP_ModularItemBase* Asset = CastChecked<USP_ModularItemBase>(AssetDataToParse.GetAsset())) Assets.Add(Asset);
        }
    }

    if(Assets.Num() < 1)
    {
        UE_LOG(LogCharacterItemWidget, Error, TEXT("%s is Empty Or Not Setting"), *AssetType.GetName().ToString());
        return;
    }
        
    for(int i = 0; i < Assets.Num(); i++)
    {
        if(Assets[i].Get() == nullptr) AssetManager.GetAsset(Assets[i]);
        if(Assets[i].Get()->Data.DisplayName.EqualTo(FText::FromString(TEXT("None"))))
        {
            CurrentItem = AssetManager.GetAsset(Assets[i]);
            SetItem();
            break;
        }
    }

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
    CurrentItem = USP_AssetManager::GetAsset(Assets[index]);
    
    UpdateTexts();
    UpdateMesh();
}

void USP_CharacterItemWidget::UpdateMesh()
{
    const auto PlayerState = GetOwningPlayer()->GetPlayerState<ASP_PlayerState>();
    PlayerState->ReplaceItemInSlot(CurrentItem);
}
