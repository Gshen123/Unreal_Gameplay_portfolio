// Scope Portfolio. All rights reserved


#include "SP_PauseWidget.h"
#include "SP_GameInstance.h"
#include "Game/SP_PlayGameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPauseWidget, All, All);

void USP_PauseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(ClearPauseButton) { ClearPauseButton->OnClicked.AddDynamic(this, &ThisClass::OnClearPause);}
    if(MainMenuButton) { MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnGoToMenu);}
    if(ExitGameButton) { ExitGameButton->OnClicked.AddDynamic(this, &ThisClass::ExitGame);}

    if(GetWorld())
        if(const auto GameMode = Cast<ASP_PlayGameModeBase>(GetWorld()->GetAuthGameMode()))
            GameMode->OnGameModeStateChanged.AddUObject(this, &ThisClass::SetVisblilityMainMenu);
}

void USP_PauseWidget::SetVisblilityMainMenu(EGameModeType Type) const
{
    if(Type == EGameModeType::MainMenu)
        MainMenuButton->SetVisibility(ESlateVisibility::Hidden);
    else if(!(Type == EGameModeType::None))
        MainMenuButton->SetVisibility(ESlateVisibility::Visible);
}

void USP_PauseWidget::OnClearPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}

void USP_PauseWidget::OnGoToMenu()
{
    const auto GameInstance = GetSP_GameInstance();
    if(!GameInstance) return;
    
    UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelData().LevelName);
}

void USP_PauseWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

USP_GameInstance* USP_PauseWidget::GetSP_GameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USP_GameInstance>();
}

