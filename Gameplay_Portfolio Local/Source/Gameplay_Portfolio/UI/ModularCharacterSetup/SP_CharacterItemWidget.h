// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Gameplay_Portfolio/Items/ModularCharacter/SP_ModularItemBase.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"
#include "SP_CharacterItemWidget.generated.h"

/**
 * 
 */

UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_CharacterItemWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* NextItemButton;

    UPROPERTY(meta = (BindWidget))
    UButton* PrevItemButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TextBlock;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* TypeTextBlock;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FPrimaryAssetType AssetType;
    
    virtual void NativeConstruct() override; 
    
private:
    UFUNCTION()
    void InitAssets();

    UFUNCTION()
    void UpdateTexts() const;
    
    UFUNCTION()
    void OnNextItem();

    UFUNCTION()
    void OnPrevItem();

    UFUNCTION()
    void SetItem();
    
    UPROPERTY()
    TArray<TSoftObjectPtr<USP_ModularItemBase>> Assets;

    UPROPERTY()
    USP_ModularItemBase* CurrentItem = nullptr;

    UPROPERTY()
    int index= 0;
};
