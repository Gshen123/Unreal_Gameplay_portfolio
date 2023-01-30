// Scope Portfolio. All rights reserved


#include "SP_MorphSliderWidget.h"

#include "Kismet/KismetMaterialLibrary.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogMorphSliderWidget, All, All);

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
    UpdateTexts();
}

void USP_MorphSliderWidget::UpdateTexts() const
{
    check(TypeTextBlock);
    TypeTextBlock->SetText(FText::FromString(MorphTargetName));
}

void USP_MorphSliderWidget::SetSliderVlaue(float value)
{
    Slider->SetValue(value);
    MaterialInstanceDynamic->SetScalarParameterValue("Value", value);
}

void USP_MorphSliderWidget::UpdateMaterial(float Value)
{
    SetSliderVlaue(Value);

    const auto LPM = GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>();
    if(LPM == nullptr) return;

    LPM->SetMorphTarget(MorphTargetName, LerpMorphValue(Value));
}

float USP_MorphSliderWidget::LerpMorphValue(float Value)
{
    if(Value > 0.5f) return Value * 2;
    if(Value == 0.5f) return 0;
    if(Value == 0.f) return -1;
    return -(1.f - Value * 2.f);
}
