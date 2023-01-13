// Fill out your copyright notice in the Description page of Project Settings.


#include "SP_MediaWidget.h"

void USP_MediaWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if(MediaPlayer && MediaSource) MediaPlayer->OpenSource(MediaSource);
}