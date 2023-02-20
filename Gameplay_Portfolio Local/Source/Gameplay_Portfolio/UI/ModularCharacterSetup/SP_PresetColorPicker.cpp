// Scope Portfolio. All rights reserved


#include "SP_PresetColorPicker.h"

#include "Subsystem/SP_LocalPlayerMeshManager.h"

void USP_PresetColorPicker::SetDefaultColor(FLinearColor Color)
{
    Loaded = true;
    DefaultColor = Color;
    ResetColor();
}

void USP_PresetColorPicker::NativeConstruct()
{
    Super::NativeConstruct();

    if(ColorButton0) ColorButton0->OnClicked.AddDynamic(this, &ThisClass::SetColor0);
    if(ColorButton1) ColorButton1->OnClicked.AddDynamic(this, &ThisClass::SetColor1);
    if(ColorButton2) ColorButton2->OnClicked.AddDynamic(this, &ThisClass::SetColor2);
    if(ColorButton3) ColorButton3->OnClicked.AddDynamic(this, &ThisClass::SetColor3);
    if(ResetButton) ResetButton->OnClicked.AddDynamic(this, &ThisClass::ResetColor);

    UpdateText();
}

void USP_PresetColorPicker::UpdateMaterial(FLinearColor Color) const
{
    const auto Subsystem = GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>();
    Subsystem->FindAndAddMaterialData(index, ParamName, Color, MaterialInstance, MakePawnType);
    Subsystem->AllUpdateMaterial(MakePawnType);

    if(Color != DefaultColor) ResetButton->SetVisibility(ESlateVisibility::Visible);
    else ResetButton->SetVisibility(ESlateVisibility::Hidden);
}

void USP_PresetColorPicker::SetColor0()
{
    UpdateMaterial(ColorButton0->WidgetStyle.Normal.TintColor.GetSpecifiedColor());
}

void USP_PresetColorPicker::SetColor1()
{
    UpdateMaterial(ColorButton1->WidgetStyle.Normal.TintColor.GetSpecifiedColor());
}

void USP_PresetColorPicker::SetColor2()
{
    UpdateMaterial(ColorButton2->WidgetStyle.Normal.TintColor.GetSpecifiedColor());
}

void USP_PresetColorPicker::SetColor3()
{
    UpdateMaterial(ColorButton3->WidgetStyle.Normal.TintColor.GetSpecifiedColor());
}

void USP_PresetColorPicker::UpdateText() const
{
    check(TypeTextBlock);
    TypeTextBlock->SetText(DisplayName);
}

void USP_PresetColorPicker::ResetColor()
{
    if(!Loaded)
    {
        DefaultColor = ColorButton0->WidgetStyle.Normal.TintColor.GetSpecifiedColor();
        Loaded = true;
    }

    UpdateMaterial(DefaultColor);
}
