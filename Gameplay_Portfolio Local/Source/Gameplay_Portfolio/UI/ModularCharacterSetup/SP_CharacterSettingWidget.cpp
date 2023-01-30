// Scope Portfolio. All rights reserved


#include "SP_CharacterSettingWidget.h"

#include "SP_AssetManager.h"
#include "SP_ModularHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"

void USP_CharacterSettingWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(MorphContainer);
    check(ClothContainer);
    check(DressSetContainer);

    MorphContainer->ClearChildren();
    ClothContainer->ClearChildren();
    DressSetContainer->ClearChildren();

    LoadedData = GetOwningPlayer()->GetHUD<ASP_ModularHUD>()->GetMeshData();

    USP_AssetManager& AssetManager = USP_AssetManager::Get();
    TArray<FPrimaryAssetType> Types = AssetManager.GetModularAsset();
    for(int i = 0;  i < Types.Num(); i++)
    {
        const auto ItemWidget = CreateWidget<USP_CharacterItemWidget>(this, CharacterItemWidgetClass);
        check(ItemWidget);
        ItemWidget->SetPadding(FMargin(0,0,0,10));
        ItemWidget->AssetType = Types[i];
        if(LoadedData.MeshItemData.IsEmpty()) ItemWidget->Init();

        if(Types[i] == USP_AssetManager::Module_SuitType)
        {
            DressSetContainer->AddChild(ItemWidget);
            SuitItemWidget = ItemWidget;
            if(const auto Name = LoadedData.MeshItemData.Find(USP_AssetManager::Module_SuitType))
            {
                ItemWidget->Init(true, *Name);
            }
        }
        else
        {
            ClothContainer->AddChild(ItemWidget);

            if(Types[i] == USP_AssetManager::Module_BodyType)
            {
                BodyItemWidget = ItemWidget;
                if(const auto Name = LoadedData.MeshItemData.Find(USP_AssetManager::Module_BodyType))
                {
                    ItemWidget->Init(true, *Name);
                }
                continue;
            }
            if(Types[i] == USP_AssetManager::Module_HeadType)
            {
                HeadItemWidget = ItemWidget;
                if(const auto Name = LoadedData.MeshItemData.Find(USP_AssetManager::Module_HeadType))
                {
                    ItemWidget->Init(true, *Name);
                }
                continue;
            }
            if(Types[i] == USP_AssetManager::Module_FeetAndLegsType)
            {
                LegItemWidget = ItemWidget;
                if(const auto Name = LoadedData.MeshItemData.Find(USP_AssetManager::Module_FeetAndLegsType))
                {
                    ItemWidget->Init(true, *Name);
                }
                continue;
            }
            if(Types[i] == USP_AssetManager::Module_HandAndArmType)
            {
                ArmItemWidget = ItemWidget;
                if(const auto Name = LoadedData.MeshItemData.Find(USP_AssetManager::Module_HandAndArmType))
                {
                    ItemWidget->Init(true, *Name);
                }
            }
        }
    }

    auto GI = GetGameInstance<USP_GameInstance>();
    TArray<FString> TargetNames = USP_AssetManager::GetAsset(GI->GetDefaultMeshParts()->Head)->K2_GetAllMorphTargetNames();
    
    for(int i = 0; i < TargetNames.Num(); i ++)
    {
        const auto ItemWidget = CreateWidget<USP_MorphSliderWidget>(this, MorphSliderWidgetClass);
        ItemWidget->SetPadding(FMargin(0,0,0,10));
        ItemWidget->MorphTargetName = TargetNames[i];
        MorphContainer->AddChild(ItemWidget);
        MorphWidgets.Add(ItemWidget);
        
        if(const auto Value = LoadedData.MorphTargetData.Find(FName(*TargetNames[i])))
        {
            ItemWidget->UpdateMaterial(*Value);
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
    if(ResetButton) ResetButton->MainButton->OnClicked.AddDynamic(this,&ThisClass::Reset);

    GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>()->WidgetUpdated.AddUObject(this, &ThisClass::UpdateWidget);
}

void USP_CharacterSettingWidget::UpdateWidget(FPrimaryAssetType Type) const
{
    if(Type == USP_AssetManager::Module_BodyType) { BodyItemWidget->SetNoneItem(); return; }
    if(Type == USP_AssetManager::Module_HeadType) { HeadItemWidget->SetNoneItem(); return;}
    if(Type == USP_AssetManager::Module_SuitType) { SuitItemWidget->SetNoneItem(); return;}
    if(Type == USP_AssetManager::Module_FeetAndLegsType) { LegItemWidget->SetNoneItem(); return;}
    if(Type == USP_AssetManager::Module_HandAndArmType) { ArmItemWidget->SetNoneItem();}
}

void USP_CharacterSettingWidget::LoadData(FPlayerMeshData Data)
{
    LoadedData = Data;
}

void USP_CharacterSettingWidget::OnIndexZero()
{
    WidgetSwitcher->SetActiveWidgetIndex(0);
    MorphContainer->SetVisibility(ESlateVisibility::Visible);
}

void USP_CharacterSettingWidget::OnIndexOne()
{
    WidgetSwitcher->SetActiveWidgetIndex(1);
    MorphContainer->SetVisibility(ESlateVisibility::Hidden);
}

void USP_CharacterSettingWidget::OnIndexTwo()
{
    WidgetSwitcher->SetActiveWidgetIndex(2);
    MorphContainer->SetVisibility(ESlateVisibility::Hidden);
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

void USP_CharacterSettingWidget::Reset()
{
    UpdateWidget(USP_AssetManager::Module_BodyType);
    UpdateWidget(USP_AssetManager::Module_HeadType);
    UpdateWidget(USP_AssetManager::Module_SuitType);
    UpdateWidget(USP_AssetManager::Module_FeetAndLegsType);
    UpdateWidget(USP_AssetManager::Module_HandAndArmType);

    GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>()->ResetMorphTargetData();
    for (USP_MorphSliderWidget* MorphWidget : MorphWidgets)
    {
        MorphWidget->SetSliderVlaue(0.5);
    }
}

USP_GameInstance* USP_CharacterSettingWidget::GetSP_GameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USP_GameInstance>();
}
