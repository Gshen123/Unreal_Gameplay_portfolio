// Scope Portfolio. All rights reserved


#include "SP_CharacterSettingWidget.h"

#include "SP_AssetManager.h"
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

    Init();
}

void USP_CharacterSettingWidget::Init()
{
    ClothContainer->ClearChildren();
    DressSetContainer->ClearChildren();
    
    auto List = USP_AssetManager::GetModularAsset();
    for(auto Type : List)
    {
        auto ItemWidget = CreateWidget<USP_CharacterItemWidget>(this);
        ItemWidget->Padding = FMargin(0,0,0,10);
        ItemWidget->AssetType = Type;

        if(Type == USP_AssetManager::Module_SuitType)
        {
            DressSetContainer->AddChild(ItemWidget);
        }
        else
        {
            ClothContainer->AddChild(ItemWidget);
        }
    }
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
    
    UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelData().LevelName);
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
