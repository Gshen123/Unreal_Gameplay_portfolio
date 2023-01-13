// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_MainMenuWidget.h"

#include "SP_GameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainMenuWidget, All, All);

void USP_MainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(StartButton) StartButton->MainButton->OnClicked.AddDynamic(this, &USP_MainMenuWidget::GameStart);
    if(LoadButton) LoadButton->MainButton->OnClicked.AddDynamic(this, &USP_MainMenuWidget::LoadGame);
    if(OptionButton) OptionButton->MainButton->OnClicked.AddDynamic(this, &USP_MainMenuWidget::ShowOptionWidget);
    if(ExitButton) ExitButton->MainButton->OnClicked.AddDynamic(this, &USP_MainMenuWidget::ShowExitModal);
}

void USP_MainMenuWidget::GameStart()
{
    if(!GetWorld()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<USP_GameInstance>();
    if(!GameInstance) return;

    if(GameInstance->GetStartupLevelData().LevelName == NAME_None)
    {
        return;
    }
    
    //const FName StartupLevelName = "Map_CharacterSettingLevel";
    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelData().LevelName);
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
    }
    
    ExitButton->SetVisibility(ESlateVisibility::Visible);
}
