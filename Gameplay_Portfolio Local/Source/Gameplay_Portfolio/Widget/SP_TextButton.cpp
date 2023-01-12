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
	FName changeProperty = PropertyChangedEvent.GetPropertyName();
	if(changeProperty == TEXT("Text_Context") || changeProperty == ("Text_FontSize") || changeProperty == ("Text_OutlineTextSize") || changeProperty == ("Text_OutlineTextColor")
		|| changeProperty == TEXT("Text_Color"))
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
	else
	{
		SetButtonColor();
	}
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void USP_TextButton::TextColorChange(FColor color) const
{
	if(TextBlock)
	{
		TextBlock->SetColorAndOpacity(color);
	}
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
		MainButton->WidgetStyle.Hovered.TintColor = Btn_HoverColor;
		MainButton->WidgetStyle.Pressed.TintColor = Btn_PressColor;
		MainButton->WidgetStyle.Disabled.TintColor = Btn_DisabledColor;

		if(Btn_OutlineRound)
		{
			FButtonStyle Style = MainButton->WidgetStyle;
			
			Style.Normal.DrawAs = ESlateBrushDrawType::Type::Box;
			Style.Normal.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
			Style.Normal.OutlineSettings.CornerRadii = Btn_OutlineConerRad;
			
			Style.Hovered.DrawAs = ESlateBrushDrawType::Type::Box;
			Style.Hovered.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
			Style.Hovered.OutlineSettings.CornerRadii = Btn_OutlineConerRad;

			Style.Pressed.DrawAs = ESlateBrushDrawType::Type::Box;
			Style.Pressed.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
			Style.Pressed.OutlineSettings.CornerRadii = Btn_OutlineConerRad;

			Style.Disabled.DrawAs = ESlateBrushDrawType::Type::Box;
			Style.Disabled.OutlineSettings.RoundingType = ESlateBrushRoundingType::Type::FixedRadius;
			Style.Disabled.OutlineSettings.CornerRadii = Btn_OutlineConerRad;
			MainButton->SetStyle(Style);
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
	
	if(TextBlock)
	{
		TextBlock->SetText(Text_Context);
	}
}

void USP_TextButton::OnButtonClicked()
{
	ScopeOnClicked.Broadcast(this);
	TextColorChange(Text_ClickColor);
	TextSizeChange(Text_ClickSize);
}

void USP_TextButton::OnButtonHoverd()
{
	ScopeOnHoverd.Broadcast(this);
	TextColorChange(Text_HoverColor);
	TextSizeChange(Text_HoverSize);
}

void USP_TextButton::OnButtonUnHoverd()
{
	ScopeOnUnHoverd.Broadcast(this);
	TextColorChange(Text_UnHoverColor);
	TextSizeChange(Text_UnHoverSize);
}

void USP_TextButton::OnButtonPressed()
{
	ScopeOnPressed.Broadcast(this);
	TextColorChange(Text_PressColor);
	TextSizeChange(Text_PressSize);
}

void USP_TextButton::OnButtonReleased()
{
	ScopeOnReleased.Broadcast(this);
	TextColorChange(Text_ReleaseColor);
	TextSizeChange(Text_ReleaseSize);
}


