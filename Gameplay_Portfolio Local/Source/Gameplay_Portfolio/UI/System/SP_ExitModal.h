// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SP_HUDBase.h"
#include "Blueprint/UserWidget.h"
#include "SP_ExitModal.generated.h"

class USP_GameInstance;
class UButton;
class USP_TextButton;
/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_ExitModal : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    USP_TextButton* GoMenuButton;

    UPROPERTY(meta = (BindWidget))
    USP_TextButton* ExitButton;
    
    UPROPERTY(meta = (BindWidget))
    UButton* CloseButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "메인메뉴 용도 여부", meta = ( ToolTip = "해당 값을 기반으로 바인딩된 위젯의 델리게이트가 설정됩니다."))
    bool bMainMenu = false;

protected:

    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnGoToMenu();

    UFUNCTION()
    void HideWidget();

    UFUNCTION()
    void GameExit();

private:

    USP_GameInstance* GetSP_GameInstance() const;

    ASP_HUDBase* GetSP_HUD() const;
};
