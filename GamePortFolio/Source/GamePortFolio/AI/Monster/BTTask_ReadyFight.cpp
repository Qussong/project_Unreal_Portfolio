// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_ReadyFight.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"

UBTTask_ReadyFight::UBTTask_ReadyFight()
{
	NodeName = TEXT("ReadyFight");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ReadyFight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (IsValid(Monster))
	{
		// REDAY_FIGHT ¸ùÅ¸ÁÖ Ãâ·Â
		Monster->SetState(EMonsterState::READYFIGHT);

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_ReadyFight::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	bool IsAttackEnd = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsReadyFight"));
	if (IsAttackEnd)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
