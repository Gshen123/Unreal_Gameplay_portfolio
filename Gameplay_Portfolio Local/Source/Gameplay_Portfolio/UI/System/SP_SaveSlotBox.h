// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_SaveSlotWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "SP_SaveSlotBox.generated.h"

/**
 * 
 */

UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_SaveSlotBox : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void SetSaveMode(EGameModeType Mode);
protected:

    virtual void NativeOnInitialized() override;
    
    virtual void NativeConstruct() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> SaveSlotWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* SlotContainer;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;
private:
    UFUNCTION()
    void HideWidget();

    UFUNCTION()
    USP_SaveSlotWidget* CreateSaveSlotWidget(FString SlotName);
    
    UPROPERTY()
    EGameModeType SaveMode;
};
