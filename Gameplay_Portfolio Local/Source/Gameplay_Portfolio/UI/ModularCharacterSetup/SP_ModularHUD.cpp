// Scope Portfolio. All rights reserved


#include "SP_ModularHUD.h"

#include "SP_CharacterSettingWidget.h"
#include "SP_PlayerState.h"
#include "Blueprint/UserWidget.h"

void ASP_ModularHUD::BeginPlay()
{
    Super::BeginPlay();

    if(CreateCharacterWidgetClass)
    {
        if(const auto CreateCharacterWidget = CreateWidget<UUserWidget>(GetWorld(), CreateCharacterWidgetClass))
        {
            CreateCharacterWidget->AddToViewport();
            const auto ModularMenu = Cast<USP_CharacterSettingWidget>(CreateCharacterWidget);
            ModularMenu->OnOptionWidget.AddUniqueDynamic(this, &ASP_ModularHUD::ShowOptionMenu);
        }
    }
}