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
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

// Boundary Section
private:
	TObjectPtr<class AGHEpicMonster> Epic;
	TObjectPtr<class APawn> Target;
	bool bAttackTime = false;
	bool bBoundaryCheck = false;
	float BoundaryRange = 500.f;
	float AttackRange;
};
