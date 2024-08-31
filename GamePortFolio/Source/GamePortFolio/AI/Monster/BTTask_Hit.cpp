// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_Hit.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h" 
#include "Character/AI/Monster/GHMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Hit::UBTTask_Hit()
{
	NodeName = TEXT("Hit");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Hit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	Monster->SetState(EMonsterState::HIT);

	return EBTNodeResult::InProgress;
}

void UBTTask_Hit::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	bool IsHit = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsHit"));
	if (false == IsHit)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_Hit::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
