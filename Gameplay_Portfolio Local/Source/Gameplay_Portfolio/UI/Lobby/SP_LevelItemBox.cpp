// Scope Portfolio. All rights reserved


#include "SP_LevelItemBox.h"

#include "SP_GameInstance.h"
#include "Kismet/GameplayStatics.h"

void USP_LevelItemBox::NativeConstruct()
{
    Super::NativeConstruct();

    if(LevelStartupButton) LevelStartupButton->MainButton->OnClicked.AddDynamic(this, &USP_LevelItemBox::LevelOpen);
}

UHorizontalBox* USP_LevelItemBox::GetLevelItemBox() const
{
    return LevelItemsBox;
}

void USP_LevelItemBox::LevelOpen()
{
    const USP_GameInstance* GameInstance = GetSP_GameInstance();
    if(!GameInstance) return;
    
    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelData().LevelName);
}

USP_GameInstance* USP_LevelItemBox::GetSP_GameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USP_GameInstance>();
}
