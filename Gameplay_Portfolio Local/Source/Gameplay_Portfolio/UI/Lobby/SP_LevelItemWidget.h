// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SP_LevelItemWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_LevelItemWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData& Data);
    FLevelData GetLevelData() const {return LevelData;}

    void SetSelected(bool IsSelected);

protected:
    
    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton;
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelImage;

    UPROPERTY(meta = (BindWidget))
    UImage* FrameImage;

    virtual void NativeConstruct() override;

private:
    FLevelData LevelData;

    UFUNCTION()
    void OnLevelItemClicked();
};
