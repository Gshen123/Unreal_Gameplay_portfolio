// Scope Portfolio. All rights reserved


#include "SP_GameOverWidget.h"
#include "SP_PlayerState.h"
#include "SP_PlayerStatRowWidget.h"
#include "SP_Utils.h"
#include "Game/SP_PlayGameModeBase.h"
#include "Gameplay_Portfolio/UI/SP_TextButton.h"
#include "Kismet/GameplayStatics.h"

void USP_GameOverWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(GetWorld())
    {
        const auto GameMode = Cast<ASP_PlayGameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnGameModeStateChanged.AddUObject(this, &ThisClass::OnGameStateTypeChanged);
        }
    }

    if(ContinueButton)
    {
        ContinueButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::OnResetLevel);
    }

    if(ExitGameButton)
    {
        ExitGameButton->MainButton->OnClicked.AddDynamic(this, &ThisClass::ShowExitModal);
    }
}

void USP_GameOverWidget::OnGameStateTypeChanged(EGameModeType State)
{
    if(State == EGameModeType::GameOver)
    {
        UpdatePlayerStat();
    }
}

void USP_GameOverWidget::OnResetLevel()
{
    //const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    //UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

void USP_GameOverWidget::ShowExitModal()
{
    if(!GameExitModal)
    {
        APlayerController* PC = Cast<APlayerController>(GetOwningPlayer());
        GameExitModal = CreateWidget<UUserWidget>( PC, GameExitModalClass );
        GameExitModal->AddToViewport();
    }
    
    ExitGameButton->SetVisibility(ESlateVisibility::Visible);
}

void USP_GameOverWidget::UpdatePlayerStat()
{
    if(!GetWorld() || !PlayerStatBox) return;

    PlayerStatBox->ClearChildren();
    
    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Cast<ASP_PlayerState>(Controller->PlayerState);
        if(!PlayerState) continue;;

        const auto PlayerStatRowWidget = CreateWidget<USP_PlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(USP_Utils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetKills(USP_Utils::TextFromInt(PlayerState->GetCoinsNum()));
        PlayerStatRowWidget->SetKills(USP_Utils::TextFromInt(PlayerState->GetLevelNum()));

        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
}
