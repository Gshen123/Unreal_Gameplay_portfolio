﻿// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"
#include "SP_MorphSliderWidget.generated.h"

/**
 * 
 */

UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_MorphSliderWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY()
    FString MorphTargetName;

    UFUNCTION()
    void SetSliderVlaue(float value);

    UFUNCTION()
    void UpdateMaterial(float Value);
    
protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TypeTextBlock;

    UPROPERTY(meta = (BindWidget))
    USlider* Slider;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    UMaterial* Material;
    
    virtual void NativeOnInitialized() override;
    
    virtual void NativeConstruct() override; 
    
private:
    
    UFUNCTION()
    void UpdateTexts() const;

    UFUNCTION()
    float LerpMorphValue(float Value);

    UPROPERTY()
    UMaterialInstanceDynamic* MaterialInstanceDynamic;
};