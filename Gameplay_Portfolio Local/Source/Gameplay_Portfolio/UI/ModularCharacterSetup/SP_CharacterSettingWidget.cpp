// Scope Portfolio. All rights reserved


#include "SP_CharacterSettingWidget.h"

#include "SP_AssetManager.h"
#include "SP_PlayerState.h"
#include "Kismet/GameplayStatics.h"

void USP_CharacterSettingWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(ClothContainer);
    check(DressSetContainer);
    
    ClothContainer->ClearChildren();
    DressSetContainer->ClearChildren();

    USP_AssetManager& AssetManager = USP_AssetManager::Get();
    TArray<FPrimaryAssetType> Types = AssetManager.GetModularAsset();
    for(int i = 0;  i < Types.Num(); i++)
    {
        const auto ItemWidget = CreateWidget<USP_CharacterItemWidget>(this, CharacterItemWidgetClass);
        check(ItemWidget);
        ItemWidget->SetPadding(FMargin(0,0,0,10));
        ItemWidget->AssetType = Types[i];
        ItemWidget->Init();

        if(Types[i] == USP_AssetManager::Module_SuitType)
        {
            DressSetContainer->AddChild(ItemWidget);
            SuitItemWidget = ItemWidget;
        }
        else
        {
            ClothContainer->AddChild(ItemWidget);

            if(Types[i] == USP_AssetManager::Module_BodyType) { BodyItemWidget = ItemWidget; continue;}
            if(Types[i] == USP_AssetManager::Module_HeadType) { HeadItemWidget = ItemWidget; continue;}
            if(Types[i] == USP_AssetManager::Module_FeetAndLegsType) { LegItemWidget = ItemWidget; continue;}
            if(Types[i] == USP_AssetManager::Module_HandAndArmType) { ArmItemWidget = ItemWidget;}
        }
    }
}


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

    GetOwningPlayer()->GetPlayerState<ASP_PlayerState>()->WidgetUpdated.AddUObject(this, &ThisClass::UpdateWidget);
}

void USP_CharacterSettingWidget::UpdateWidget(FPrimaryAssetType Type) const
{
    if(Type == USP_AssetManager::Module_BodyType) { BodyItemWidget->SetNoneItem(); return; }
    if(Type == USP_AssetManager::Module_HeadType) { HeadItemWidget->SetNoneItem(); return;}
    if(Type == USP_AssetManager::Module_SuitType) { SuitItemWidget->SetNoneItem(); return;}
    if(Type == USP_AssetManager::Module_FeetAndLegsType) { LegItemWidget->SetNoneItem(); return;}
    if(Type == USP_AssetManager::Module_HandAndArmType) { ArmItemWidget->SetNoneItem();}
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
