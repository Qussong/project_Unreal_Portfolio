// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_MoveToTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = TEXT("TraceTarget");
	AcceptableRadius = 50.f;
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AGHMonster* Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();

	if (IsValid(Monster))
	{
		Monster->SetState(EMonsterState::TRACE);
	}
	else
	{
		Result = EBTNodeResult::Failed;
	}

	return Result;
}
