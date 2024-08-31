// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_Attack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"


UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->SetState(EMonsterState::ATTACK);
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//Normal Monster Section
	bool IsAttackEnd = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsAttackEnd"));
	if (IsAttackEnd)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttackEnd"), false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}