// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GHBaseWidget.h"

UGHBaseWidget::UGHBaseWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGHBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGHBaseWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
