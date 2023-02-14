// Scope Portfolio. All rights reserved


#include "SP_MorphSliderWidget.h"

#include "Kismet/KismetMaterialLibrary.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogMorphSliderWidget, All, All);

FORCEINLINE float LerpMorphValue(float Value) {return Value * 2 - 1;}

void USP_MorphSliderWidget::NativeOnInitialized()
{
    MaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, Material);

    FSlateBrush Brush1 = FSlateBrush();
    Brush1.SetResourceObject(MaterialInstanceDynamic);
    Brush1.ImageSize = FVector2d(256,256);
    
    FSlateBrush Brush2 = FSlateBrush();
    Brush2.ImageSize = FVector2d(0,0);
    Brush2.DrawAs = ESlateBrushDrawType::NoDrawType;

    FSliderStyle Style = FSliderStyle();
    Style.SetNormalBarImage(Brush1);
    Style.SetHoveredBarImage(Brush1);
    Style.SetDisabledBarImage(Brush1);
    Style.SetNormalThumbImage(Brush2);
    Style.SetHoveredThumbImage(Brush2);
    Style.SetHoveredThumbImage(Brush2);
    Style.BarThickness = 18.f;

    Slider->SetWidgetStyle(Style);
    
    Super::NativeOnInitialized();
}

void USP_MorphSliderWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    Slider->OnValueChanged.AddDynamic(this, &ThisClass::UpdateMaterial);
    if(ResetButton) ResetButton->OnClicked.AddDynamic(this, &ThisClass::ResetMorphTarget);
    UpdateTexts();
}

void USP_MorphSliderWidget::UpdateTexts() const
{
    check(TypeTextBlock);
    TypeTextBlock->SetText(DisplayName);
}

void USP_MorphSliderWidget::SetSliderVlaue(float Value)
{
    Slider->SetValue(Value);
    MaterialInstanceDynamic->SetScalarParameterValue("Value", Value);
}

void USP_MorphSliderWidget::UpdateMaterial(float Value)
{
    SetSliderVlaue(Value);
    GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>()->SetMorphTarget(MorphTargetName, LerpMorphValue(Value));

    if(Value != DefaultValue) ResetButton->SetVisibility(ESlateVisibility::Visible);
    else ResetButton->SetVisibility(ESlateVisibility::Hidden);
}

void USP_MorphSliderWidget::SetDefaultVlaue(float Value)
{
    Loaded = true;
    DefaultValue = Value;
    UpdateMaterial(Value);
}

void USP_MorphSliderWidget::ResetMorphTarget()
{
    UpdateMaterial(DefaultValue);
}

void USP_MorphSliderWidget::SetMorphTargetDefalutOrValue(float Value)
{
    if(Loaded)
    {
        ResetMorphTarget();
        return;
    }

    SetSliderVlaue(Value);
}
