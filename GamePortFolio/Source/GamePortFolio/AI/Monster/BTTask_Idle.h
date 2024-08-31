// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Idle.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UBTTask_Idle : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Idle();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	TObjectPtr<class AGHMonster> Monster;
};
