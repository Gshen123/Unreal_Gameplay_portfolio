// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_ExitModal.h"

#include "SP_GameInstance.h"
#include "SP_HUDBase.h"
#include "Components/Button.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogExitModal, All, All);

void USP_ExitModal::NativeConstruct()
{
    Super::NativeConstruct();

    // 해당 클래스는 각 게임모드마다 관리방식이 달라짐. 해당 프로젝트에선 하드 레벨 관리를 하기 때문에 자동으로 언바인딩됨 
    // 게임모드가 메뉴인 상태일 때 델리게이트 ( GoMenuButton = 게임종료 , ExitButton = 취소 , CloseButton = 창 숨기기 )
    if(bMainMenu)
    {
        if(GoMenuButton) { GoMenuButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::GameExit);}
        if(ExitButton) { ExitButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::HideWidget);}
        if(CloseButton) CloseButton->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
       // 게임모드가 플레이일 경우, (GoMenuButton = 메인메뉴 이동, ExitButton = 게임종료, CloseButton = 창 숨기기 )
        if(GoMenuButton) { GoMenuButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::OnGoToMenu);}
        if(ExitButton) { ExitButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::GameExit);}
        if(CloseButton) { ExitButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::HideWidget);}
    }
}

void USP_ExitModal::OnGoToMenu()
{
    const auto GameInstance = GetSP_GameInstance();
    if(!GameInstance) return;
    
    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelData().LevelName);
}

void USP_ExitModal::HideWidget()
{
    GetSP_HUD()->RemoveWidgetInStack(this);
}

void USP_ExitModal::GameExit()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

USP_GameInstance* USP_ExitModal::GetSP_GameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USP_GameInstance>();
}

ASP_HUDBase* USP_ExitModal::GetSP_HUD() const
{
    const auto HUD = Cast<ASP_HUDBase>(GetOwningPlayer()->GetHUD());

    if(!HUD) return nullptr;
    return HUD;
}
