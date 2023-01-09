// Fill out your copyright notice in the Description page of Project Settings.


#include "SPTextButton.h"

void USPTextButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if(TextBlock)
	{
		if(!text.IsEmpty())
		{
			TextBlock->SetText(text);
			TextSizeChange(FontSize);
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
	if(PropertyChangedEvent.GetPropertyName() == TEXT("text"))
	{
		if(TextBlock)
		{
			if(!text.IsEmpty())
			{
				TextBlock->SetText(text);
				TextSizeChange(FontSize);
			}
		}
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

void USPTextButton::OnButtonClicked()
{
	ScopeOnClicked.Broadcast(this);
	TextColorChange(ClickColor);
	TextSizeChange(ClickSize);
}

void USPTextButton::OnButtonHoverd()
{
	ScopeOnHoverd.Broadcast(this);
	TextColorChange(HoverColor);
	TextSizeChange(HoverSize);
}

void USPTextButton::OnButtonUnHoverd()
{
	ScopeOnUnHoverd.Broadcast(this);
	TextColorChange(UnHoverColor);
	TextSizeChange(UnHoverSize);
}

void USPTextButton::OnButtonPressed()
{
	ScopeOnPressed.Broadcast(this);
	TextColorChange(PressColor);
	TextSizeChange(PressSize);
}

void USPTextButton::OnButtonReleased()
{
	ScopeOnReleased.Broadcast(this);
	TextColorChange(ReleaseColor);
	TextSizeChange(ReleaseSize);
}


