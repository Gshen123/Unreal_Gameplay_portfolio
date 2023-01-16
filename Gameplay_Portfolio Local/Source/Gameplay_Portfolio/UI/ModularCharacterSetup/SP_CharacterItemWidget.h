// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "SP_CharacterItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_CharacterItemWidget : public UUserWidget
{
    GENERATED_BODY()

public:


protected:
    UPROPERTY(meta = (BindWidget))
    UButton* NextItemButton;

    UPROPERTY(meta = (BindWidget))
    UButton* PrevItemButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TextBlock;

    UPROPERTY(meta = (BindWidget))
    UBackgroundBlur* Blur;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FPrimaryAssetType AssetType;
    
    virtual void NativeOnInitialized() override; 
    
private:
    UFUNCTION()
    void InitAssets();

    UFUNCTION()
    void UpdateTexts() const;
    
    UFUNCTION()
    void OnNextItem();

    UFUNCTION()
    void OnPrevItem();
    
    UPROPERTY()
    TArray<TSoftObjectPtr<USP_ModularItemBase>> Assets;

    UPROPERTY()
    USP_ModularItemBase* CurrentItem = nullptr;
};
