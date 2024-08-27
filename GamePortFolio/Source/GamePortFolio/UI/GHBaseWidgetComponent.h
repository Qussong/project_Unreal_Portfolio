// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GHBaseWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHBaseWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UGHBaseWidgetComponent();

public:
	virtual void OnRegister() override;
	virtual void InitWidget() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
