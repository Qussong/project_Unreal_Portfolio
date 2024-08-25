// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/GHPlayerWidget.h"
#include "Components/ProgressBar.h"

UGHPlayerWidget::UGHPlayerWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UGHPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("GHHealthBar")));
	ManaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("GHManaBar")));
	StaminaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("GHStaminaBar")));
	EXPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("GHEXPBar")));
}

void UGHPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
