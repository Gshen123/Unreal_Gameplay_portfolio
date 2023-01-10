// Fill out your copyright notice in the Description page of Project Settings.


#include "SPTextButton.h"

void USPTextButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if(TextBlock)
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
void USPTextButton::NativeConstruct()
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
void USPTextButton::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
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

void USPTextButton::TextColorChange(FColor color) const
{
	if(TextBlock)
	{
		TextBlock->SetColorAndOpacity(color);
	}
}

void USPTextButton::TextSizeChange(int size) const
{
	if(TextBlock)
	{
		FSlateFontInfo FontInfo = TextBlock->GetFont();
		FontInfo.Size = size;
		TextBlock->SetFont(FontInfo);
	}
}

inline void USPTextButton::SetButtonColor() const
{
	if(MainButton)
	{
		MainButton->WidgetStyle.Normal.TintColor = Btn_NormalColor;
		MainButton->WidgetStyle.Hovered.TintColor = Btn_HoverColor;
		MainButton->WidgetStyle.Pressed.TintColor = TBtn_PressColor;
		MainButton->WidgetStyle.Disabled.TintColor = Btn_DisabledColor;
	}
}

void USPTextButton::ChangeOutlineTextProperty() const
{
	if(TextBlock)
	{
		FSlateFontInfo FontInfo = TextBlock->GetFont();
		FontInfo.OutlineSettings.OutlineColor = Text_OutlineTextColor;
		FontInfo.OutlineSettings.OutlineSize = Text_OutlineTextSize;
		TextBlock->SetFont(FontInfo);
	}
}


void USPTextButton::OnButtonClicked()
{
	ScopeOnClicked.Broadcast(this);
	TextColorChange(Text_ClickColor);
	TextSizeChange(Text_ClickSize);
}

void USPTextButton::OnButtonHoverd()
{
	ScopeOnHoverd.Broadcast(this);
	TextColorChange(Text_HoverColor);
	TextSizeChange(Text_HoverSize);
}

void USPTextButton::OnButtonUnHoverd()
{
	ScopeOnUnHoverd.Broadcast(this);
	TextColorChange(Text_UnHoverColor);
	TextSizeChange(Text_UnHoverSize);
}

void USPTextButton::OnButtonPressed()
{
	ScopeOnPressed.Broadcast(this);
	TextColorChange(Text_PressColor);
	TextSizeChange(Text_PressSize);
}

void USPTextButton::OnButtonReleased()
{
	ScopeOnReleased.Broadcast(this);
	TextColorChange(Text_ReleaseColor);
	TextSizeChange(Text_ReleaseSize);
}


