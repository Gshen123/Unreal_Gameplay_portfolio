// Scope Portfolio. All rights reserved


#include "SP_CharacterSettingWidget.h"
#include "SP_AssetManager.h"
#include "SP_ModularHUD.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/SP_LocalPlayerMeshManager.h"

constexpr FLinearColor ANIM_ACTIVE_NORMAL_COLOR = FLinearColor(0.598958,0.393962, 0.188026,0.800000);
constexpr FLinearColor ANIM_ACTIVE_HOVERED_COLOR = FLinearColor(0.598958,0.433307,0.277778,0.800000);
constexpr FLinearColor ANIM_ACTIVE_PRESSED_COLOR = FLinearColor(0.598958,0.501839,0.434240,0.800000);
constexpr FLinearColor ANIM_DEACTIVE_NORMAL_COLOR = FLinearColor(0.162396,0.373665, 0.598958,0.800000);
constexpr FLinearColor ANIM_DEACTIVE_HOVERED_COLOR = FLinearColor(0.245798,0.410574,0.598958,0.800000);
constexpr FLinearColor ANIM_DEACTIVE_PRESSED_COLOR = FLinearColor(0.366765,0.480153,0.598958,0.800000);

void USP_CharacterSettingWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(ClothContainer);
    check(DressSetContainer);
    
    ClothContainer->ClearChildren();
    DressSetContainer->ClearChildren();

    check(MorphHeadContainer);
    check(MorphBrowContainer);
    check(MorphEyeContainer);
    check(MorphNoseContainer);
    check(MorphMouseContainer);
    check(MorphJawContainer);
    MorphHeadContainer->ClearChildren();
    MorphBrowContainer->ClearChildren();
    MorphEyeContainer->ClearChildren();
    MorphNoseContainer->ClearChildren();
    MorphMouseContainer->ClearChildren();
    MorphJawContainer->ClearChildren();
    
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
                if(const auto Name = LoadedData.MeshItemData.Find(USP_AssetManager::Module_FeetAndLegsType)) ItemWidget->Init(true, *Name);
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

    if(HairMaterial.Get() == nullptr) USP_AssetManager::GetAsset(HairMaterial);
    if(BreadMaterial0.Get() == nullptr) USP_AssetManager::GetAsset(BreadMaterial0);
    if(BreadMaterial1.Get() == nullptr) USP_AssetManager::GetAsset(BreadMaterial1);
    if(BreadMaterial2.Get() == nullptr) USP_AssetManager::GetAsset(BreadMaterial2);
    
    MorphHeadContainer->AddChild(CreateColorPickerWidget(20, TEXT("머리 색상"), TEXT("Base Color Tint"), HairMaterial.Get()));
    MorphBrowContainer->AddChild(CreateMorphWidget("Brow_Raise_Inner_L", TEXT("눈썹 안쪽 좌측")));
    MorphBrowContainer->AddChild(CreateMorphWidget("Brow_Raise_Inner_R", TEXT("눈썹 안쪽 우측")));
    MorphBrowContainer->AddChild(CreateMorphWidget("Brow_Raise_Outer_L", TEXT("눈썹 외곽 좌측")));
    MorphBrowContainer->AddChild(CreateMorphWidget("Brow_Raise_Outer_R", TEXT("눈썹 외곽 우측")));
    MorphBrowContainer->AddChild(CreateMorphWidget("Brow_Drop_L", TEXT("눈썹 좌측 높이")));
    MorphBrowContainer->AddChild(CreateMorphWidget("Brow_Drop_R", TEXT("눈썹 우측 높이")));
    MorphEyeContainer->AddChild(CreateMorphWidget("Eye_Blink", TEXT("눈 감는 정도")));
    MorphEyeContainer->AddChild(CreateMorphWidget("Eye_Wide_L", TEXT("눈 좌측 크기")));
    MorphEyeContainer->AddChild(CreateMorphWidget("Eye_Wide_R", TEXT("눈 우측 크기")));
    MorphNoseContainer->AddChild(CreateMorphWidget("Nose_Flanks_Raise", TEXT("콧구멍 넓이")));
    MorphNoseContainer->AddChild(CreateMorphWidget("A23_Nose_Sneer_Left", TEXT("코 좌측 기울임 정도")));
    MorphNoseContainer->AddChild(CreateMorphWidget("A24_Nose_Sneer_Right", TEXT("코 우측 기울임 정도")));
    MorphJawContainer->AddChild(CreateColorPickerWidget(17, TEXT("턱수염 색상 1"), TEXT("Base Color Tint"), BreadMaterial0.Get()));
    MorphJawContainer->AddChild(CreateColorPickerWidget(18, TEXT("콧수염 색상"), TEXT("Base Color Tint"), BreadMaterial1.Get()));
    MorphJawContainer->AddChild(CreateColorPickerWidget(19, TEXT("턱수염 색상 2"), TEXT("Base Color Tint"), BreadMaterial2.Get()));
    MorphMouseContainer->AddChild(CreateMorphWidget("Wide", TEXT("입 넓이")));
    MorphMouseContainer->AddChild(CreateMorphWidget("Mouth_Frown", TEXT("입 꼬리")));
    MorphMouseContainer->AddChild(CreateMorphWidget("Mouth_Up", TEXT("입 높이")));
}


void USP_CharacterSettingWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(WidgetSwitcher)
    {
        if(SwitcherButton1) SwitcherButton1->MainButton->OnClicked.AddDynamic(this, &ThisClass::SwictherToIndexZero);
        if(SwitcherButton2) SwitcherButton2->MainButton->OnClicked.AddDynamic(this, &ThisClass::SwictherToIndexOne);
        if(SwitcherButton3) SwitcherButton3->MainButton->OnClicked.AddDynamic(this, &ThisClass::SwictherToIndexTwo);
    }

    if(ReturnButton) ReturnButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::OnGoToMenu);
    if(OptionButton) OptionButton->MainButton->OnClicked.AddDynamic(this,&ThisClass::ShowOptionWidget);
    if(ResetButton) ResetButton->MainButton->OnClicked.AddDynamic(this,&ThisClass::Reset);

    if(AnimButton1) AnimButton1->OnClicked.AddDynamic(this, &ThisClass::UpdateAnimZero);
    if(AnimButton2) AnimButton2->OnClicked.AddDynamic(this, &ThisClass::UpdateAnimOne);
    if(AnimButton3) AnimButton3->OnClicked.AddDynamic(this, &ThisClass::UpdateAnimTwo);

    const auto LPM = GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>();
    LPM->WidgetUpdated.AddUObject(this, &ThisClass::UpdateWidget);
    for (const auto MergeComponent : LPM->GetMergeComponents())
    {
        ModuluarCharacter = Cast<ASP_PlayerCharacter>(MergeComponent->GetOwner());
    }
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

USP_MorphSliderWidget* USP_CharacterSettingWidget::CreateMorphWidget(FString MorphName, FString DisplayName)
{
    const auto ItemWidget = CreateWidget<USP_MorphSliderWidget>(this, MorphSliderWidgetClass);
    ItemWidget->SetPadding(FMargin(0,0,0,10));
    ItemWidget->MorphTargetName = MorphName;
    ItemWidget->DisplayName = FText::FromString(*DisplayName);
    MorphWidgets.Add(ItemWidget);
    if(const auto Value = LoadedData.MorphTargetData.Find(FName(*MorphName))) ItemWidget->UpdateMaterial(*Value);

    return ItemWidget;
}

USP_PresetColorPicker* USP_CharacterSettingWidget::CreateColorPickerWidget(int32 Index, FString DisplayName, FString ParamName,
    UMaterialInstance* MaterialInstance)
{
    const auto ItemWidget = CreateWidget<USP_PresetColorPicker>(this, ColorPickerWidgetClass);
    ItemWidget->SetPadding(FMargin(0,0,0,10));
    ItemWidget->index = Index;
    ItemWidget->ParamName = FName(*ParamName);
    ItemWidget->DisplayName = FText::FromString(*DisplayName);
    ItemWidget->MaterialInstance = MaterialInstance;
    
    return ItemWidget;
}

void USP_CharacterSettingWidget::SwictherToIndexZero()
{
    WidgetSwitcher->SetActiveWidgetIndex(0);
    if(ModuluarCharacter)
    {
        ModuluarCharacter.Get()->GetCameraBoom()->TargetArmLength = 60.f;
        ModuluarCharacter.Get()->GetFollowCamera()->SetRelativeLocation(FVector(0,-3,70));
    }
}

void USP_CharacterSettingWidget::SwictherToIndexOne()
{
    WidgetSwitcher->SetActiveWidgetIndex(1);
    if(ModuluarCharacter)
    {
        ModuluarCharacter.Get()->GetCameraBoom()->TargetArmLength = 250.f;
        ModuluarCharacter.Get()->GetFollowCamera()->SetRelativeLocation(FVector::ZeroVector);
    }
}

void USP_CharacterSettingWidget::SwictherToIndexTwo()
{
    WidgetSwitcher->SetActiveWidgetIndex(2);
    if(ModuluarCharacter)
    {
        ModuluarCharacter.Get()->GetCameraBoom()->TargetArmLength = 250.f;
        ModuluarCharacter.Get()->GetFollowCamera()->SetRelativeLocation(FVector::ZeroVector);
    }
}

void USP_CharacterSettingWidget::UpdateAnimZero()
{
    if(AnimIndex == 0) return;
    if(!IdleAnim) return;

    FButtonStyle Style = AnimButton1->WidgetStyle;
    Style.Normal.TintColor = ANIM_ACTIVE_NORMAL_COLOR;
    Style.Hovered.TintColor = ANIM_ACTIVE_HOVERED_COLOR;
    Style.Pressed.TintColor = ANIM_ACTIVE_PRESSED_COLOR;
    AnimButton1->SetStyle(Style);

    Style.Normal.TintColor = ANIM_DEACTIVE_NORMAL_COLOR;
    Style.Hovered.TintColor = ANIM_DEACTIVE_HOVERED_COLOR;
    Style.Pressed.TintColor = ANIM_DEACTIVE_PRESSED_COLOR;
    
    if(AnimIndex == 1) AnimButton2->SetStyle(Style);
    if(AnimIndex == 2) AnimButton3->SetStyle(Style);
    
    AnimIndex = 0;
    GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>()->UpdateAnimation(IdleAnim);
}

void USP_CharacterSettingWidget::UpdateAnimOne()
{
    if(AnimIndex == 1) return;
    if(!IdleAnim) return;

    FButtonStyle Style = AnimButton2->WidgetStyle;
    Style.Normal.TintColor = ANIM_ACTIVE_NORMAL_COLOR;
    Style.Hovered.TintColor = ANIM_ACTIVE_HOVERED_COLOR;
    Style.Pressed.TintColor = ANIM_ACTIVE_PRESSED_COLOR;
    AnimButton2->SetStyle(Style);

    Style.Normal.TintColor = ANIM_DEACTIVE_NORMAL_COLOR;
    Style.Hovered.TintColor = ANIM_DEACTIVE_HOVERED_COLOR;
    Style.Pressed.TintColor = ANIM_DEACTIVE_PRESSED_COLOR;
    
    if(AnimIndex == 0) AnimButton1->SetStyle(Style);
    if(AnimIndex == 2) AnimButton3->SetStyle(Style);
    
    AnimIndex = 1;
    GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>()->UpdateAnimation(WalkAnim);
}

void USP_CharacterSettingWidget::UpdateAnimTwo()
{
    if(AnimIndex == 2) return;
    if(!IdleAnim) return;

    FButtonStyle Style = AnimButton3->WidgetStyle;
    Style.Normal.TintColor = ANIM_ACTIVE_NORMAL_COLOR;
    Style.Hovered.TintColor = ANIM_ACTIVE_HOVERED_COLOR;
    Style.Pressed.TintColor = ANIM_ACTIVE_PRESSED_COLOR;
    AnimButton3->SetStyle(Style);

    Style.Normal.TintColor = ANIM_DEACTIVE_NORMAL_COLOR;
    Style.Hovered.TintColor = ANIM_DEACTIVE_HOVERED_COLOR;
    Style.Pressed.TintColor = ANIM_DEACTIVE_PRESSED_COLOR;
    
    if(AnimIndex == 0) AnimButton1->SetStyle(Style);
    if(AnimIndex == 1) AnimButton2->SetStyle(Style);
    
    AnimIndex = 2;
    GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>()->UpdateAnimation(RunAnim);
}

void USP_CharacterSettingWidget::OnGoToMenu()
{
    const auto GameInstance = GetSP_GameInstance();
    if(!GameInstance) return;
    
    GetOwningLocalPlayer()->GetSubsystem<USP_LocalPlayerMeshManager>()->Deinitialize();
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
    for (USP_MorphSliderWidget* MorphWidget : MorphWidgets) MorphWidget->SetSliderVlaue(0.5);
}

USP_GameInstance* USP_CharacterSettingWidget::GetSP_GameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USP_GameInstance>();
}
