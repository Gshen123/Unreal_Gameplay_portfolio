// Scope Portfolio. All rights reserved


#include "SP_SaveSlotBox.h"

#include "SP_HUDBase.h"

void USP_SaveSlotBox::SetSaveMode(EGameModeType Mode)
{
    SaveMode = Mode;
}

void USP_SaveSlotBox::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void USP_SaveSlotBox::NativeConstruct()
{
    Super::NativeConstruct();
    
    if(!SlotContainer) return;
    SlotContainer->ClearChildren();
    CreateSaveSlotWidget(TEXT("AutoSave"));
    CreateSaveSlotWidget(TEXT("Slot_01"));
    CreateSaveSlotWidget(TEXT("Slot_02"));
    CreateSaveSlotWidget(TEXT("Slot_03"));
    
    if(ExitButton) ExitButton->OnClicked.AddDynamic(this, &ThisClass::HideWidget);
}

void USP_SaveSlotBox::HideWidget()
{
    const auto HUD = Cast<ASP_HUDBase>(GetOwningPlayer()->GetHUD());
    HUD->RemoveWidgetInStack(this);
}

USP_SaveSlotWidget* USP_SaveSlotBox::CreateSaveSlotWidget(FString SlotName)
{
    const auto SettingWidget = CreateWidget<USP_SaveSlotWidget>(this, SaveSlotWidgetClass);
    SettingWidget->SetPadding(FMargin(0, 7.5f, 0, 7.5f));
    SettingWidget->SlotName = SlotName;
    SettingWidget->SetSaveMode(SaveMode);
    SlotContainer->AddChild(SettingWidget);
    return SettingWidget;
}
