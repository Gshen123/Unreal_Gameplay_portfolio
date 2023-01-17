// Scope Portfolio. All rights reserved


#include "SP_CharacterSettingWidget.h"

#include "Kismet/GameplayStatics.h"

void USP_CharacterSettingWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(WidgetSwitcher)
    {
        if(SwitcherButton1) SwitcherButton1->MainButton->OnClicked.AddDynamic(this, &ThisClass::OnIndexZero);
        if(SwitcherButton2) SwitcherButton2->MainButton->OnClicked.AddDynamic(this, &ThisClass::OnIndexOne);
        if(SwitcherButton3) SwitcherButton3->MainButton->OnClicked.AddDynamic(this, &ThisClass::OnIndexTwo);
    }

    if(ReturnButton) ReturnButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::OnGoToMenu);
    if(OptionButton) OptionButton->MainButton->OnClicked.AddDynamic(this,&ThisClass::ShowOptionWidget);
}

void USP_CharacterSettingWidget::OnIndexZero()
{
    WidgetSwitcher->SetActiveWidgetIndex(0);
}

void USP_CharacterSettingWidget::OnIndexOne()
{
    WidgetSwitcher->SetActiveWidgetIndex(1);
}

void USP_CharacterSettingWidget::OnIndexTwo()
{
    WidgetSwitcher->SetActiveWidgetIndex(2);
}

void USP_CharacterSettingWidget::OnGoToMenu()
{
    const auto GameInstance = GetSP_GameInstance();
    if(!GameInstance) return;
    
    UGameplayStatics::OpenLevel(this, GameInstance->GetLevelsData()[0].LevelName);
}

void USP_CharacterSettingWidget::ShowOptionWidget()
{
    OnOptionWidget.Broadcast();
}

USP_GameInstance* USP_CharacterSettingWidget::GetSP_GameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USP_GameInstance>();
}
