// Scope Portfolio. All rights reserved


#include "SP_CharacterItemWidget.h"

#include "SP_AssetManager.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacterItemWidget, All, All);

void USP_CharacterItemWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if(NextItemButton) NextItemButton->OnClicked.AddDynamic(this, &ThisClass::OnNextItem);
    if(PrevItemButton) PrevItemButton->OnClicked.AddDynamic(this, &ThisClass::OnPrevItem);
    if(ResetButton) ResetButton->OnClicked.AddDynamic(this, &ThisClass::ResetItem);
}

void USP_CharacterItemWidget::Init(bool Loaded, FName ItemName)
{
    USP_AssetManager& AssetManager = USP_AssetManager::Get();
    
    TArray<FPrimaryAssetId> AssetIDs; 
    AssetManager.GetPrimaryAssetIdList(AssetType, AssetIDs);

    for(const FPrimaryAssetId ID : AssetIDs)
    {
        FAssetData AssetDataToParse;
        AssetManager.GetPrimaryAssetData(ID, AssetDataToParse);
        if(auto NameFilter = AssetDataToParse.AssetName.ToString(); NameFilter != "Default")
            if(const USP_ModularItemBase* Asset = CastChecked<USP_ModularItemBase>(AssetDataToParse.GetAsset())) Assets.Add(Asset);
    }

    if(Assets.Num() < 1)
    {
        UE_LOG(LogCharacterItemWidget, Error, TEXT("%s is Empty Or Not Setting"), *AssetType.GetName().ToString());
        return;
    }
        
    for(int i = 0; i < Assets.Num(); i++)
    {
        if(!Assets[i].Get()) AssetManager.GetAsset(Assets[i]);
        if(Assets[i].Get()->Data.DisplayName.EqualTo(FText::FromString(TEXT("None"))) && !Loaded)
        {
            DefaultItemName = TEXT("None");
            DefaultIndex = i;
            index = DefaultIndex;
            UpdateItem();
            break;
        }
        if(Assets[i].Get()->Data.DisplayName.EqualTo(FText::FromName(ItemName)))
        {
            DefaultItemName = ItemName;
            DefaultIndex = i;
            index = DefaultIndex;
            UpdateItem();
            break;
        }
    }

    for(auto Asset : Assets)
        UE_LOG(LogCharacterItemWidget, Display, TEXT("%s : %s"), *AssetType.GetName().ToString(), *Asset.Get()->Data.DisplayName.ToString());
}


void USP_CharacterItemWidget::UpdateText() const
{
    if(CurrentItem)
    {
        TextBlock->SetText(CurrentItem->GetDisplayName());
        TypeTextBlock->SetText(FText::FromString(AssetType.ToString()));
    }
}

void USP_CharacterItemWidget::OnNextItem()
{
    if(index < Assets.Num() - 1) index++;
    else index = 0;

    UpdateItem();
}

void USP_CharacterItemWidget::OnPrevItem()
{
    if(index > 0) index--;
    else index = Assets.Num() - 1;

    UpdateItem();
}

void USP_CharacterItemWidget::UpdateItem()
{
    if(index != DefaultIndex) ResetButton->SetVisibility(ESlateVisibility::Visible);
    else ResetButton->SetVisibility(ESlateVisibility::Hidden);
    
    CurrentItem = USP_AssetManager::GetAsset(Assets[index]);
    UpdateText();
    const auto MeshManager =GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>();
    MeshManager->FindAndAddMeshItemData(AssetType, CurrentItem->Data.DisplayName.ToString(), MakePawnType);
    MeshManager->ReplaceItemInSlot(CurrentItem, MakePawnType, DefaultItemName);
}

void USP_CharacterItemWidget::ResetItem()
{
    index = DefaultIndex;
    UpdateItem();
}
