// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/GHPlayerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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

	CurHealthTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("GHCurrentHealth")));
	MaxHealthTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("GHMaxHealth")));
	CurManaTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("GHCurrentMana")));
	MaxManaTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("GHMaxMana")));
}

void UGHPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
