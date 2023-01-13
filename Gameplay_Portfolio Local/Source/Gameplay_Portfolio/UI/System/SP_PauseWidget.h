// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "Blueprint/UserWidget.h"
#include "SP_PauseWidget.generated.h"

class USP_TextButton;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPauseWidgetOption);

UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_PauseWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    virtual void NativeConstruct() override;

    UFUNCTION()
    void SetMainMenuButtonVisble(EGameModeType Type) const;

    UPROPERTY()
    FPauseWidgetOption PauseWidgetOptionDelegate;
protected:
    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ClearPauseButton;
    
    UPROPERTY(meta = (BindWidget))
    USP_TextButton* MainMenuButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* SettingsButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ExitGameButton;

private:
    UFUNCTION()
    void OnClearPause();

    UFUNCTION()
    void OnGoToMenu();

    UFUNCTION()
    void ExitGame();

    UFUNCTION()
    void ShowOptionWidget();
};
