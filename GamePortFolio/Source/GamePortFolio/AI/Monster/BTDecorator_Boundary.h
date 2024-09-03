// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Boundary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UBTDecorator_Boundary : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_Boundary();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	float BoundartDistance = 500.f;
};
