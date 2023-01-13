// Scope Portfolio. All rights reserved


#include "SP_PlayerStatRowWidget.h"

void USP_PlayerStatRowWidget::SetPlayerName(const FText& Text)
{
    if(!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}

void USP_PlayerStatRowWidget::SetKills(const FText& Text)
{
    if(!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}

void USP_PlayerStatRowWidget::SetCoins(const FText& Text)
{
    if(!CoinTextBlock) return;
    CoinTextBlock->SetText(Text);
}

void USP_PlayerStatRowWidget::SetLevel(const FText& Text)
{
    if(!LevelTextBlock) return;
    LevelTextBlock->SetText(Text);
}
