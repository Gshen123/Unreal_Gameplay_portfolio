// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_MainMenuWidget.h"

#include "SP_GameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainMenuWidget, All, All);

void USP_MainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(StartButton) StartButton->MainButton->OnClicked.AddDynamic(this, &USP_MainMenuWidget::ShowSelectedLevel);
    if(LoadButton) LoadButton->MainButton->OnClicked.AddDynamic(this, &USP_MainMenuWidget::LoadGame);
    if(OptionButton) OptionButton->MainButton->OnClicked.AddDynamic(this, &USP_MainMenuWidget::ShowOptionWidget);
    if(ExitButton) ExitButton->MainButton->OnClicked.AddDynamic(this, &USP_MainMenuWidget::ShowExitModal);


    InitLevelItems();
}

void USP_MainMenuWidget::InitLevelItems()
{
    const auto GameInstance = GetSP_GameInstance();
    if(!GameInstance) return;

    checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if(!LevelItemBox) return;
    LevelItemBox->GetLevelItemBox()->ClearChildren();

    for(auto LevelData: GameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<USP_LevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        const auto LevelItemWidgetCasted = Cast<USP_LevelItemWidget>(LevelItemWidget);
        if(!LevelItemWidgetCasted) return;

        LevelItemWidgetCasted->SetLevelData(LevelData);
        LevelItemWidgetCasted->OnLevelSelected.AddUObject(this, &ThisClass::OnLevelSelected);
        LevelItemWidgetCasted->SetPadding(FMargin(15,15,15,15));

        LevelItemBox->GetLevelItemBox()->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if(GameInstance->GetStartupLevelData().LevelName.IsNone())
    {
        OnLevelSelected(GameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(GameInstance->GetStartupLevelData());
    }
}

void USP_MainMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto GameInstance = GetSP_GameInstance();
    if(!GameInstance) return;

    GameInstance->SetStartupLevelData(Data);

    for(const auto LevelItemWidget : LevelItemWidgets)
    {
        if(LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void USP_MainMenuWidget::LoadGame()
{
    
}

void USP_MainMenuWidget::ShowOptionWidget()
{
    MainMenuOptionDelegate.Broadcast();
}

void USP_MainMenuWidget::ShowExitModal()
{
    if(!ExitModal)
    {
        APlayerController* PC = Cast<APlayerController>(GetOwningPlayer());
        ExitModal = CreateWidget<UUserWidget>( PC, ExitModalClass );
        ExitModal->AddToViewport();
        GetSP_MenuHUD()->PushWidgetStack(ExitModal);
    }
    
    GetSP_MenuHUD()->PushWidgetStack(ExitModal);
}

void USP_MainMenuWidget::ShowSelectedLevel()
{
    if(!LevelItemBox) return;
    if(LevelItemBox->GetVisibility() == ESlateVisibility::Visible) return;

    UE_LOG(LogMainMenuWidget, Display, TEXT("Selected Level Please"));
    GetSP_MenuHUD()->PushWidgetStack(LevelItemBox);
}

USP_GameInstance* USP_MainMenuWidget::GetSP_GameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USP_GameInstance>();
}

ASP_MenuHUD* USP_MainMenuWidget::GetSP_MenuHUD() const
{
    const auto HUD = Cast<ASP_MenuHUD>(GetOwningPlayer()->GetHUD());
    if(!HUD) return nullptr;

    return HUD;
}
