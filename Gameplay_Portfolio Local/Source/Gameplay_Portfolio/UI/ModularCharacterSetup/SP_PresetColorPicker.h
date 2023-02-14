// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SP_PresetColorPicker.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_PresetColorPicker : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void SetDefaultColor(FLinearColor Color);

    UFUNCTION()
    void ResetColor();
    
    UPROPERTY()
    FText DisplayName;

    UPROPERTY()
    int32 index;

    UPROPERTY()
    FName ParamName;

    UPROPERTY()
    UMaterialInstance* MaterialInstance;
    
protected:

    virtual void NativeConstruct() override;

    void UpdateMaterial(FLinearColor Color) const;

    UFUNCTION()
    void SetColor0();
    UFUNCTION()
    void SetColor1();
    UFUNCTION()
    void SetColor2();
    UFUNCTION()
    void SetColor3();
    UFUNCTION()
    void UpdateText() const;
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TypeTextBlock;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ColorButton0;

    UPROPERTY(meta = (BindWidget))
    UButton* ColorButton1;

    UPROPERTY(meta = (BindWidget))
    UButton* ColorButton2;

    UPROPERTY(meta = (BindWidget))
    UButton* ColorButton3;

    UPROPERTY()
    bool Loaded = false;
    
    UPROPERTY()
    FLinearColor DefaultColor;
};
