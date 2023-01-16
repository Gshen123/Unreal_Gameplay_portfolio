// Scope Portfolio. All rights reserved


#include "SP_LevelItemWidget.h"

#include "SP_GameInstance.h"
#include "Components/Button.h"

class USP_GameInstance;

void USP_LevelItemWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(LevelSelectButton) {LevelSelectButton->OnClicked.AddDynamic(this, &ThisClass::OnLevelItemClicked);}
}

void USP_LevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USP_LevelItemWidget::SetLevelData(const FLevelData& Data)
{
    LevelData = Data;

    if(LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
    }
    if(LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumb);
    }
}

void USP_LevelItemWidget::SetSelected(bool IsSelected)
{
    if(FrameImage)
    {
        FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}
