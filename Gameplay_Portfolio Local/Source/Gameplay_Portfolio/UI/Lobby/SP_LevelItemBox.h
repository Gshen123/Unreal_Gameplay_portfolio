// Scope Portfolio. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Overlay.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"
#include "SP_LevelItemBox.generated.h"

class USP_GameInstance;
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_LevelItemBox : public UUserWidget
{
    GENERATED_BODY()

public:
    UHorizontalBox* GetLevelItemBox() const;

protected:
    
    virtual void NativeConstruct() override;

    UFUNCTION()
    void LevelOpen();
    
    UPROPERTY(meta = (BindWidget))
    UButton* LevelStartupButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

private:
    USP_GameInstance* GetSP_GameInstance() const;
};
