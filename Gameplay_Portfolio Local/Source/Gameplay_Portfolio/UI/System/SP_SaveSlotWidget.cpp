// Scope Portfolio. All rights reserved


#include "SP_SaveSlotWidget.h"

#include <string>

#include "SP_PlayerState.h"
#include "Subsystem/SP_SaveGameSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogSaveSlotWidget, All, All);

void USP_SaveSlotWidget::SetSaveMode(EGameModeType Mode)
{
    NowSaveMode = Mode;
}

void USP_SaveSlotWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void USP_SaveSlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(SelectButton) SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnSlotClicked);
    if(DeleteSaveButton) DeleteSaveButton->OnClicked.AddDynamic(this, &ThisClass::DeleteSaveGame);
    InitData(GetSaveGameSubsystem()->LoadSaveGame(SlotName, NowSaveMode));
}

void USP_SaveSlotWidget::InitData(USP_SaveGame* Data) const
{
    if(Data == nullptr)
    {
        WidgetSwitcher->SetActiveWidgetIndex(0);
        DeleteSaveButton->SetVisibility(ESlateVisibility::Hidden);
        return;
    }
    GameModeText->SetText(UEnum::GetDisplayValueAsText(NowSaveMode));
    SaveTimeText->SetText(FText::FromString(Data->DateTime.ToString()));
    SaveSlotText->SetText(FText::FromString(SlotName));
    PlayTimeText->SetText(FText::FromString(Data->GetPlayerData(GetOwningPlayerState())->GetPlayTime()));
    WidgetSwitcher->SetActiveWidgetIndex(1);
    DeleteSaveButton->SetVisibility(ESlateVisibility::Visible);
}

void USP_SaveSlotWidget::SaveData() const
{
    GetSaveGameSubsystem()->WriteSaveGame(SlotName, NowSaveMode);
    InitData(GetSaveGameSubsystem()->GetCurrentSaveGame());
}

void USP_SaveSlotWidget::LoadData() const
{
    GetSaveGameSubsystem()->LoadSaveGame(SlotName, NowSaveMode);
}

void USP_SaveSlotWidget::DeleteSaveGame()
{
    GetSaveGameSubsystem()->DeleteSaveGame(SlotName);
    InitData(GetSaveGameSubsystem()->GetCurrentSaveGame());
}

void USP_SaveSlotWidget::OnSlotClicked()
{
    if(NowSaveMode == EGameModeType::None)
    {
        if(WidgetSwitcher->GetActiveWidgetIndex()) LoadData();
        else SaveData();
    }
    else if(NowSaveMode == EGameModeType::CharacterSetup) SaveData();
    else LoadData();
}

USP_SaveGameSubsystem* USP_SaveSlotWidget::GetSaveGameSubsystem() const
{
    return GetGameInstance()->GetSubsystem<USP_SaveGameSubsystem>();
}
