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
            NoneIndex = i;
            if(!Loaded)
            {
                index = NoneIndex;
                UpdateItem();
                break;
            }
        }
        else if(Assets[i].Get()->Data.DisplayName.EqualTo(FText::FromName(ItemName)))
        {
            index = i;
            UpdateItem();
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

    UpdateItem();
}

void USP_CharacterItemWidget::OnPrevItem()
{
    if(index > 0) index--;
    else index = Assets.Num() - 1;

    UpdateItem();
}

void USP_CharacterItemWidget::UpdateItem(bool NoUpdate)
{
    CurrentItem = USP_AssetManager::GetAsset(Assets[index]);
    GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>()->FindAndAddMeshItemData(AssetType, FName(*CurrentItem->Data.DisplayName.ToString()));
    UpdateTexts();

    if(!NoUpdate) UpdateMesh();
}

void USP_CharacterItemWidget::UpdateMesh() const
{
    const auto LPM = GetOwningPlayer()->GetLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>();
    LPM->ReplaceItemInSlot(CurrentItem);
}

void USP_CharacterItemWidget::SetNoneItem()
{
    index =  NoneIndex;
    UpdateItem();
}