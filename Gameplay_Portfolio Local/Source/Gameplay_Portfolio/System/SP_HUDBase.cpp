// Scope Portfolio. All rights reserved

#include "SP_HUDBase.h"

#include "Blueprint/UserWidget.h"
#include "Gameplay_Portfolio/UI/System/SP_MainOptionWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogHUDBase, All, All);

void ASP_HUDBase::ShowOptionMenu()
{
    if(OptionMenu) return;
    
    APlayerController* PC = Cast<APlayerController>(GetOwner());
    OptionMenu = CreateWidget<UUserWidget>( PC, OptionMenuClass );
    OptionMenu->AddToViewport();

    auto OptionWidget = Cast<USP_MainOptionWidget>(OptionMenu);
    OptionWidget->GraphicTabBtn->SetFocus();
    OptionWidget->ExitBtn->OnClicked.AddUniqueDynamic(this, &ASP_HUDBase::HideOptionMenu);

    PushWidgetStack(OptionWidget);
}

void ASP_HUDBase::HideOptionMenu()
{
    if (OptionMenu)
    {
        OptionMenu->RemoveFromParent();
        RemoveWidgetInStack(OptionMenu);
        OptionMenu = nullptr;
    }
}

void ASP_HUDBase::AllHideWidget()
{
    if(CurrentVisibleWidget)
    {
        CurrentVisibleWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    CurrentVisibleWidget = nullptr;

    for(const auto Widget : WidgetStack)
    {
        Widget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ASP_HUDBase::PushWidgetStack(UUserWidget* Widget)
{
    AllHideWidget();
    
    if(!WidgetStack.Contains(Widget)) WidgetStack.Add(Widget);
    CurrentVisibleWidget = Widget;
    
    Widget->SetVisibility(ESlateVisibility::Visible);

    for(auto i : WidgetStack)
    {
        UE_LOG(LogHUDBase, Warning, TEXT("Widget Name : %s "), *Widget->GetName());
    }
}

UUserWidget* ASP_HUDBase::PopWidgetStack()
{
    if(WidgetStack.IsEmpty()) return nullptr;
    
    const auto Widget = WidgetStack.Pop();
    WidgetStack.Remove(Widget);
    Widget->SetVisibility(ESlateVisibility::Hidden);
    UE_LOG(LogHUDBase, Warning, TEXT("Widget Name : %s "), *Widget->GetName());
    
    return Widget;
}

void ASP_HUDBase::RemoveWidgetInStack(UUserWidget* Widget)
{
    if(!WidgetStack.Contains(Widget)) WidgetStack.Add(Widget);
    Widget->SetVisibility(ESlateVisibility::Hidden);
}
