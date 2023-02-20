// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
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

    UFUNCTION()
    void SetSliderVlaue(float Value);

    UFUNCTION()
    void UpdateMaterial(float Value);

    UFUNCTION()
    void SetDefaultVlaue(float Value);

    UFUNCTION()
    void SetMorphTargetDefalutOrValue(float Value);
    
    UPROPERTY()
    FString MorphTargetName;

    UPROPERTY()
    FText DisplayName;

    UPROPERTY()
    EMergePawnType MakePawnType;
    
protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TypeTextBlock;

    UPROPERTY(meta = (BindWidget))
    USlider* Slider;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    UMaterial* Material;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetButton;
    
    virtual void NativeOnInitialized() override;
    
    virtual void NativeConstruct() override; 
    
private:
    
    UFUNCTION()
    void UpdateTexts() const;

    UFUNCTION()
    void ResetMorphTarget();

    UPROPERTY()
    bool Loaded = false;
    
    UPROPERTY()
    float DefaultValue = 0.f;
    
    UPROPERTY()
    UMaterialInstanceDynamic* MaterialInstanceDynamic;
};