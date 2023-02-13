// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Subsystem/SP_SaveGameSubsystem.h"
#include "SP_SaveSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_SaveSlotWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    
    UPROPERTY()
    FString SlotName = TEXT("");

    UFUNCTION()
    void SetSaveMode(EGameModeType Mode);

protected:
    virtual void NativeOnInitialized() override;
    
    virtual void NativeConstruct() override;
    
    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* WidgetSwitcher;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SaveSlotText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SaveTimeText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayTimeText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ChapterText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* GameModeText;
    
    UPROPERTY(meta = (BindWidget))
    UImage* ChapterImage;

    UPROPERTY(meta = (BindWidget))
    UButton* SelectButton;

    UPROPERTY(meta = (BindWidget))
    UButton* DeleteSaveButton;
    
private:
    UFUNCTION()
    void InitData(USP_SaveGame* Data) const;
    
    UFUNCTION()
    void SaveData() const;

    UFUNCTION()
    void LoadData() const;

    UFUNCTION()
    void OnSlotClicked();

    UFUNCTION()
    void DeleteSaveGame();
    
    USP_SaveGameSubsystem* GetSaveGameSubsystem() const;

    UPROPERTY()
    EGameModeType NowSaveMode = EGameModeType::None;
};
