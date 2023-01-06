// Fill out your copyright notice in the Description page of Project Settings.


#include "SPMediaWidget.h"

void USPMediaWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(MediaPlayer && MediaSource) MediaPlayer->OpenSource(MediaSource);
}