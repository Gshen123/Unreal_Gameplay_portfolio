// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CharacterItemWidget.h"
#include "SP_GameInstance.h"
#include "SP_MorphSliderWidget.h"
#include "SP_PlayerCharacter.h"
#include "SP_PresetColorPicker.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"
#include "System/SP_SaveSlotBox.h"
#include "SP_HUDBase.h"
#include "SP_CharacterSettingWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FModularWidgetOption, bool, OtherHide);
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
    USP_CharacterItemWidget* BodyItemWidget;

    UPROPERTY()
    USP_CharacterItemWidget* ArmItemWidget;

    UPROPERTY()
    USP_CharacterItemWidget* LegItemWidget;

    UPROPERTY()
    USP_CharacterItemWidget* SuitItemWidget;

    UPROPERTY()
    TObjectPtr<ASP_PlayerCharacter> ModuluarCharacter;

    UPROPERTY()
    EMergePawnType MakePawnType;
    
    UFUNCTION()
    void ResetItemWidget(FPrimaryAssetType Type) const;
    
    void LoadData();
    
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
    UButton* CreateCharacterButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ResetButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ReturnButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* OptionButton;
    
    UPROPERTY(meta = (BindWidget))
    UScrollBox* MorphHeadContainer;

    UPROPERTY(meta = (BindWidget))
    UScrollBox* MorphBrowContainer;

    UPROPERTY(meta = (BindWidget))
    UScrollBox* MorphEyeContainer;

    UPROPERTY(meta = (BindWidget))
    UScrollBox* MorphNoseContainer;

    UPROPERTY(meta = (BindWidget))
    UScrollBox* MorphMouseContainer;

    UPROPERTY(meta = (BindWidget))
    UScrollBox* MorphJawContainer;
    
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* ClothContainer;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* DressSetContainer;

    UPROPERTY(meta = (BindWidget))
    UButton* AnimButton1;

    UPROPERTY(meta = (BindWidget))
    UButton* AnimButton2;

    UPROPERTY(meta = (BindWidget))
    UButton* AnimButton3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<USP_CharacterItemWidget> CharacterItemWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<USP_MorphSliderWidget> MorphSliderWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<USP_PresetColorPicker> ColorPickerWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<USP_SaveSlotBox> SaveSlotBoxWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Material")
    TSoftObjectPtr<UMaterialInstance> HairMaterial;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Material")
    TSoftObjectPtr<UMaterialInstance> BreadMaterial0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Material")
    TSoftObjectPtr<UMaterialInstance> BreadMaterial1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Material")
    TSoftObjectPtr<UMaterialInstance> BreadMaterial2;
    
private:
    UFUNCTION()
    USP_MorphSliderWidget* CreateMorphWidget(FString MorphName, FString DisplayName);

    UFUNCTION()
    USP_PresetColorPicker* CreateColorPickerWidget(int32 Index, FString DisplayName, FString ParamName, UMaterialInstance* MaterialInstance);
    
    UFUNCTION()
    void WidgetSwictherIndexZero();
    
    UFUNCTION()
    void WidgetSwictherIndexOne();
    
    UFUNCTION()
    void WidgetSwictherIndexTwo();

    UFUNCTION()
    void UpdateAnimZero();

    UFUNCTION()
    void UpdateAnimOne();

    UFUNCTION()
    void UpdateAnimTwo();
    
    UFUNCTION()
    void GoToLobby();

    UFUNCTION()
    void ShowOptionWidget();

    UFUNCTION()
    void Reset();

    UFUNCTION()
    void CreateSaveSlotWidget();

    UFUNCTION()
    void OpenGameLevel();

    UFUNCTION()
    USP_GameInstance* GetSP_GameInstance() const;

    UFUNCTION()
    ASP_HUDBase* GetSP_HUD() const;

    UPROPERTY()
    FSaveMeshData LoadedData;

    UPROPERTY()
    USP_SaveSlotBox* SaveSlotBox;

    UPROPERTY()
    TArray<USP_CharacterItemWidget*> CharacterItemWidgets;
    
    UPROPERTY()
    TArray<USP_MorphSliderWidget*> MorphWidgets;

    UPROPERTY()
    TArray<USP_PresetColorPicker*> ColorPickerWidgets;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
    UAnimationAsset* IdleAnim;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
    UAnimationAsset* WalkAnim;

    UPROPERTY()
    int AnimIndex = 0;
};
