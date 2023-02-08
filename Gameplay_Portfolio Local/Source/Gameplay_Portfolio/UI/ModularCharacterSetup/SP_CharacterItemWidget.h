﻿// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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

public:
    UPROPERTY(EditAnywhere)
    FPrimaryAssetType AssetType;

    UPROPERTY()
    TArray<TSoftObjectPtr<USP_ModularItemBase>> Assets;
    
    TShaderRef<int32> test;

    UFUNCTION()
    void SetNoneItem();
    
    void Init(bool Loaded = false, FName ItemName = NAME_None);
    
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* NextItemButton;

    UPROPERTY(meta = (BindWidget))
    UButton* PrevItemButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetButton;
    
    UPROPERTY(meta = (BindWidget))
    USP_TextButton* TextBlock;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* TypeTextBlock;
    
    virtual void NativeConstruct() override; 
    
private:
    
    UFUNCTION()
    void UpdateTexts() const;
    
    UFUNCTION()
    void OnNextItem();

    UFUNCTION()
    void OnPrevItem();

    UFUNCTION()
    void UpdateItem(bool NoUpdate = false);

    UFUNCTION()
    void UpdateMesh() const;

    UFUNCTION()
    void Reset();
    
    UPROPERTY()
    USP_ModularItemBase* CurrentItem = nullptr;

    UPROPERTY()
    int NoneIndex = 0;
    
    UPROPERTY()
    int index= 0;
};
