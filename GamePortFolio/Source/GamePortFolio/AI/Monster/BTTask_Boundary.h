// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Boundary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UBTTask_Boundary : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Boundary();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	TObjectPtr<class AGHMonster> Monster;
	TObjectPtr<APawn> Target;
	float BoundarySpeed = 25.f;
};
