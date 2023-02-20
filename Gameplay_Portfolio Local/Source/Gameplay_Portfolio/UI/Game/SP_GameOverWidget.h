// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "SP_GameOverWidget.generated.h"

class USP_TextButton;
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_GameOverWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    virtual void NativeConstruct() override;
    
protected:
    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ContinueButton;
    
    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ExitGameButton;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> GameExitModalClass;
    
    UFUNCTION()
    void ShowExitModal();

private:
    void UpdatePlayerStat();
    void OnGameStateTypeChanged(EGameModeType ChangeType);

    UFUNCTION()
    void OnResetLevel();
    
    UPROPERTY()
    UUserWidget* GameExitModal;
};
