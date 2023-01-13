// Scope Portfolio. All rights reserved


#include "SP_PauseWidget.h"

#include "SP_GameInstance.h"
#include "SP_GameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"
#include "Kismet/GameplayStatics.h"

void USP_PauseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(ClearPauseButton) { ClearPauseButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::OnClearPause);}
    if(MainMenuButton) { MainMenuButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::OnGoToMenu);}
    if(SettingsButton) { SettingsButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::ShowOptionWidget);}
    if(ExitGameButton) { ExitGameButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::ExitGame);}

    if(GetWorld())
    {
        const auto GameMode = Cast<ASP_GameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnGameModeStateChanged.AddUObject(this, &ThisClass::SetMainMenuButtonVisble);
        }
    }
}

void USP_PauseWidget::SetMainMenuButtonVisble(EGameModeType Type) const
{
    if(Type == EGameModeType::MainMenu)
    {
        MainMenuButton->SetVisibility(ESlateVisibility::Hidden);
    }
    else if(!(Type == EGameModeType::None))
    {
        MainMenuButton->SetVisibility(ESlateVisibility::Visible);
    }
}

void USP_PauseWidget::OnClearPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}

void USP_PauseWidget::OnGoToMenu()
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

void USP_PauseWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USP_PauseWidget::ShowOptionWidget()
{
    PauseWidgetOptionDelegate.Broadcast();
}

