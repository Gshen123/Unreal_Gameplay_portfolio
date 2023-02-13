// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_TextButton.h"

void USP_TextButton::NativePreConstruct()
{
    Super::NativePreConstruct();
	
    if(TextBlock && MainButton)
    {
        if(!Text_Context.IsEmpty())
        {
            TextBlock->SetText(Text_Context);
            TextSizeChange(Text_FontSize);
            SetButtonColor();
            ChangeOutlineTextProperty();
            TextColorChange(Text_Color);
        }
    }
}

// 인게임에서 델리게이트 바인딩을 적용합니다. 
void USP_TextButton::NativeConstruct()
{
    Super::NativeConstruct();

    if(MainButton)
    {
        MainButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonClicked);
        MainButton->OnHovered.AddUniqueDynamic(this, &ThisClass::OnButtonHoverd);
        MainButton->OnPressed.AddUniqueDynamic(this, &ThisClass::OnButtonPressed);
        MainButton->OnReleased.AddUniqueDynamic(this, &ThisClass::OnButtonReleased);
        MainButton->OnUnhovered.AddUniqueDynamic(this, &ThisClass::OnButtonUnHoverd);
    }
}

#if WITH_EDITOR
void USP_TextButton::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    const FName ChangeProperty = PropertyChangedEvent.GetPropertyName();
    if(ChangeProperty == TEXT("Text_Context") || ChangeProperty == ("Text_FontSize") || ChangeProperty == ("Text_OutlineTextSize") || ChangeProperty == ("Text_OutlineTextColor")
          || ChangeProperty == TEXT("Text_Color"))
    {
        if(TextBlock)
        {
            if(!Text_Context.IsEmpty())
            {
                TextBlock->SetText(Text_Context);
                TextSizeChange(Text_FontSize);
                ChangeOutlineTextProperty();
                TextColorChange(Text_Color);
            }
        }
    }
    else SetButtonColor();
	
    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void USP_TextButton::TextColorChange(FColor color) const
{
    if(TextBlock) TextBlock->SetColorAndOpacity(color);
}

void USP_TextButton::TextSizeChange(int size) const
{
    if(TextBlock)
    {
        FSlateFontInfo FontInfo = TextBlock->GetFont();
        FontInfo.Size = size;
        TextBlock->SetFont(FontInfo);
    }
}

inline void USP_TextButton::SetButtonColor() const
{
    if(MainButton)
    {
        MainButton->WidgetStyle.Normal.TintColor = Btn_NormalColor;
        MainButton->WidgetStyle.Normal.OutlineSettings.Color = Btn_OutlineColor;
        MainButton->WidgetStyle.Normal.OutlineSettings.Width = bBtn_OutlineWidth;
        MainButton->WidgetStyle.Hovered.TintColor = Btn_HoverColor;
        MainButton->WidgetStyle.Hovered.OutlineSettings.Color = Btn_OutlineColor;
        MainButton->WidgetStyle.Hovered.OutlineSettings.Width = bBtn_OutlineWidth;
        MainButton->WidgetStyle.Pressed.TintColor = Btn_PressColor;
        MainButton->WidgetStyle.Pressed.OutlineSettings.Color = Btn_OutlineColor;
        MainButton->WidgetStyle.Pressed.OutlineSettings.Width = bBtn_OutlineWidth;
        MainButton->WidgetStyle.Disabled.TintColor = Btn_DisabledColor;
        MainButton->WidgetStyle.Disabled.OutlineSettings.Color = Btn_OutlineColor;
        MainButton->WidgetStyle.Disabled.OutlineSettings.Width = bBtn_OutlineWidth;

        if(bBtn_OutlineRound)
        {
            FButtonStyle Style = MainButton->WidgetStyle;
		    
            ESlateBrushRoundingType::Type roundtype;
            if(bBtn_RoundTypeisFixedRadius) roundtype = ESlateBrushRoundingType::FixedRadius;
            else { roundtype = ESlateBrushRoundingType::HalfHeightRadius;}
		    
            Style.Normal.DrawAs = ESlateBrushDrawType::Type::RoundedBox;
            Style.Normal.OutlineSettings.RoundingType = roundtype;
            Style.Normal.OutlineSettings.CornerRadii = Btn_OutlineConerRad;
			
            Style.Hovered.DrawAs = ESlateBrushDrawType::Type::RoundedBox;
            Style.Hovered.OutlineSettings.RoundingType = roundtype;
            Style.Hovered.OutlineSettings.CornerRadii = Btn_OutlineConerRad;

            Style.Pressed.DrawAs = ESlateBrushDrawType::Type::RoundedBox;
            Style.Pressed.OutlineSettings.RoundingType = roundtype;
            Style.Pressed.OutlineSettings.CornerRadii = Btn_OutlineConerRad;

            Style.Disabled.DrawAs = ESlateBrushDrawType::Type::RoundedBox;
            Style.Disabled.OutlineSettings.RoundingType = roundtype;
            Style.Disabled.OutlineSettings.CornerRadii = Btn_OutlineConerRad;
            MainButton->SetStyle(Style);
        }

        if(!Btn_CursorType == 0)
        {
            if(Btn_CursorType == 1) MainButton->SetCursor(EMouseCursor::Type::Hand);
            else if(Btn_CursorType == 2) MainButton->SetCursor(EMouseCursor::Type::GrabHand);
            else MainButton->SetCursor(EMouseCursor::Type::GrabHandClosed);
        }
    }
}

void USP_TextButton::ChangeOutlineTextProperty() const
{
    if(TextBlock)
    {
        FSlateFontInfo FontInfo = TextBlock->GetFont();
        FontInfo.OutlineSettings.OutlineColor = Text_OutlineTextColor;
        FontInfo.OutlineSettings.OutlineSize = Text_OutlineTextSize;
        TextBlock->SetFont(FontInfo);
    }
}

void USP_TextButton::SetText(FText Content)
{
    Text_Context = Content;
    if(TextBlock) TextBlock->SetText(Text_Context);
}

void USP_TextButton::OnButtonClicked()
{
    TextColorChange(Text_ClickColor);
    TextSizeChange(Text_ClickSize);
}

void USP_TextButton::OnButtonHoverd()
{
    TextColorChange(Text_HoverColor);
    TextSizeChange(Text_HoverSize);
}

void USP_TextButton::OnButtonUnHoverd()
{
    TextColorChange(Text_UnHoverColor);
    TextSizeChange(Text_UnHoverSize);
}

void USP_TextButton::OnButtonPressed()
{
    TextColorChange(Text_PressColor);
    TextSizeChange(Text_PressSize);
}

void USP_TextButton::OnButtonReleased()
{
    TextColorChange(Text_ReleaseColor);
    TextSizeChange(Text_ReleaseSize);
}


