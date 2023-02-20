// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SP_CoreType.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "SP_PauseWidget.generated.h"

class USP_GameInstance;
class USP_TextButton;
/**
 * 
 */

UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_PauseWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    virtual void NativeConstruct() override;

    UFUNCTION()
    void SetVisblilityMainMenu(EGameModeType Type) const;

    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;
    
    UPROPERTY(meta = (BindWidget))
    UButton* MainMenuButton;

    UPROPERTY(meta = (BindWidget))
    UButton* OptionButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitGameButton;
    
protected:

private:
    UFUNCTION()
    void OnClearPause();

    UFUNCTION()
    void OnGoToMenu();

    UFUNCTION()
    void ExitGame();

    USP_GameInstance* GetSP_GameInstance() const;
};
