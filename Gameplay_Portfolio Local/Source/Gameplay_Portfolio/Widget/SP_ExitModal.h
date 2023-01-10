// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPTextButton.h"
#include "Blueprint/UserWidget.h"
#include "SP_ExitModal.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_PORTFOLIO_API USP_ExitModal : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|기본",  meta = (DisplayPriority = 1))
	USPTextButton* YesButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "버튼|기본",  meta = (DisplayPriority = 2))
	USPTextButton* NoButton;
};
