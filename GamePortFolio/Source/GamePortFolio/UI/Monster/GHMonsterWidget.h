// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GHBaseWidget.h"
#include "GHMonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHMonsterWidget : public UGHBaseWidget
{
	GENERATED_BODY()
	
public:
	UGHMonsterWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct();	// Init
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);	// Tick

};
