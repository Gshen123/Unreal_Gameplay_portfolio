// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "SPMediaWidget.generated.h"

/**
 * 위젯 상에서 동영상이 실행되도록 자동화한 위젯입니다.
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEPLAY_PORTFOLIO_API USPMediaWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "기본|에셋", meta = (DisplayPriority = 0))
	UImage* Image;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere , Category = "기본|에셋", meta = (DisplayPriority = 1))
	UMediaPlayer* MediaPlayer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere , Category = "기본|에셋", meta = (DisplayPriority = 2))
	UMediaSource* MediaSource;
};
