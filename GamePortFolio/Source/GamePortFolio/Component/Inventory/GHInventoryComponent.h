// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/BaseActorComponent.h"
#include "GHInventoryComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHInventoryComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:
	UGHInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
