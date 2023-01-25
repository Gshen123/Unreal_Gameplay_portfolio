// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CharacterItemWidget.h"
#include "SP_GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"
#include "SP_CharacterSettingWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FModularWidgetOption);
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_CharacterSettingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FModularWidgetOption OnOptionWidget;

    UPROPERTY()
    USP_CharacterItemWidget* HeadItemWidget;

    UPROPERTY()
    USP_CharacterItemWidget* ItemWidget;

    UPROPERTY()
    USP_CharacterItemWidget* HeadItemWidget;

    UPROPERTY()
    USP_CharacterItemWidget* HeadItemWidget;

    UPROPERTY()
    USP_CharacterItemWidget* HeadItemWidget;
    
protected:

    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* WidgetSwitcher;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* SwitcherButton1;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* SwitcherButton2;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* SwitcherButton3;
    
    UPROPERTY(meta = (BindWidget))
    USP_TextButton* CreateCharacterButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ResetButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ReturnButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* OptionButton;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* ClothContainer;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* DressSetContainer;
    
private:
    UFUNCTION()
    void Init();
    
    UFUNCTION()
    void OnIndexZero();
    
    UFUNCTION()
    void OnIndexOne();
    
    UFUNCTION()
    void OnIndexTwo();

    UFUNCTION()
    void OnGoToMenu();

    UFUNCTION()
    void ShowOptionWidget();

    USP_GameInstance* GetSP_GameInstance() const;
};
