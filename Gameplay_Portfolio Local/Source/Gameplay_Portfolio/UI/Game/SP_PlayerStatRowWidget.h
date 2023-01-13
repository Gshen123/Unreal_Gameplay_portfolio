// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SP_PlayerStatRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_PlayerStatRowWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetCoins(const FText& Text);
    void SetLevel(const FText& Text);
    
protected:

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* CoinTextBlock;
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelTextBlock;
    
};
