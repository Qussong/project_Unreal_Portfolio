// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Item/GHItemWidget.h"
#include "GHPickupWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHPickupWidget : public UGHItemWidget
{
	GENERATED_BODY()
	
public:
	UGHPickupWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct();	// Init
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);	// Tick
};
