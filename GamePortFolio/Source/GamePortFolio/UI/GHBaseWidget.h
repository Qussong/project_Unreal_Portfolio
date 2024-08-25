// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GHBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGHBaseWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct();	// Init
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);	// Tick

};
