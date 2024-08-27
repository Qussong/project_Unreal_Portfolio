// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GHBaseWidgetComponent.h"
#include "GHItemWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHItemWidgetComponent : public UGHBaseWidgetComponent
{
	GENERATED_BODY()
	
public:
	UGHItemWidgetComponent();

public:
	virtual void OnRegister() override;
	virtual void InitWidget() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
