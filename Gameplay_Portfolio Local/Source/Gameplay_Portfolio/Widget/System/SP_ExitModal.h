// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SP_ExitModal.generated.h"

class USP_TextButton;
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

	UPROPERTY(meta = (BindWidget))
	USP_TextButton* YesButton;

	UPROPERTY(meta = (BindWidget))
	USP_TextButton* NoButton;
};
