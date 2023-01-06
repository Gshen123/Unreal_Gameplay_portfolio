// Fill out your copyright notice in the Description page of Project Settings.


#include "SPTextButton.h"

void USPTextButton::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USPTextButton::NativeConstruct()
{
	Super::NativeConstruct();

	MainButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonClicked);
	MainButton->OnHovered.AddUniqueDynamic(this, &ThisClass::OnButtonHoverd);
	MainButton->OnPressed.AddUniqueDynamic(this, &ThisClass::OnButtonUnHoverd);
	MainButton->OnReleased.AddUniqueDynamic(this, &ThisClass::OnButtonPressd);
	MainButton->OnUnhovered.AddUniqueDynamic(this, &ThisClass::OnButtonReleased);

	if(TextBlock)
	{
		if(!text.IsEmpty())
		{
			TextBlock->SetText(text);
		}
	}
}

void USPTextButton::TextColorChange(FColor color) const
{
	if(TextBlock)
	{
		TextBlock->SetColorAndOpacity(color);
	}
}


void USPTextButton::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	if(PropertyChangedEvent.GetPropertyName()==TEXT("Content Text"))
	{
		if(TextBlock)
		{
			if(!text.IsEmpty())
			{
				TextBlock->SetText(text);
			}
		}
	}
	else if(PropertyChangedEvent.GetPropertyName()==TEXT("Text"))
	{
		if(TextBlock)
		{
			text = TextBlock->GetText();
			TextBlock->SetText(text);
		}
	}
	
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}

void USPTextButton::OnButtonClicked()
{
	ScopeOnClicked.Broadcast(this);
	TextColorChange(ClickColor);
}

void USPTextButton::OnButtonHoverd()
{
	ScopeOnHoverd.Broadcast(this);
	TextColorChange(HoverColor);
}

void USPTextButton::OnButtonUnHoverd()
{
	ScopeOnUnHoverd.Broadcast(this);
	TextColorChange(UnHoverColor);
}

void USPTextButton::OnButtonPressd()
{
	ScopeOnPressed.Broadcast(this);
	TextColorChange(PressColor);
}

void USPTextButton::OnButtonReleased()
{
	ScopeOnReleased.Broadcast(this);
	TextColorChange(ReleaseColor);
}


