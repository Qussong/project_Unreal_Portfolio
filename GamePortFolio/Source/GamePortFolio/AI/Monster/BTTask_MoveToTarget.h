// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UBTTask_MoveToTarget : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveToTarget();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
