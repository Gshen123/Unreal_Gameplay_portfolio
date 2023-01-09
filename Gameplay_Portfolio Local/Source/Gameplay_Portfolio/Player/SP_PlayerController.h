// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SP_PlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEPLAY_PORTFOLIO_API ASP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;
};
