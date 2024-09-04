// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_MoveToTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Character/AI/Monster/Epic/GHEpicMonster.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = TEXT("TraceTarget");
	AcceptableRadius = 50.f;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AGHMonster* Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if(nullptr == Monster) return EBTNodeResult::Failed;

	Monster->SetState(EMonsterState::TRACE);

	Epic = Cast<AGHEpicMonster>(Monster);
	if (IsValid(Epic))
	{
		// Boundary Section
		Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
		bAttackTime = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsAttackTime"));
		bBoundaryCheck = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsCheckBoundary"));

		// Attack Section
		if (bAttackTime)
		{
			AttackRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("AttackRange"));
		}
	}

	return Result;
}

void UBTTask_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(IsValid(Epic))
	{
		float DistanceToTarget = Epic->GetDistanceTo(Target);	// Target 과 Monster 사이의 거리

		// Boundary Section
		if (bAttackTime == false
			&& bBoundaryCheck == false)
		{
			if (DistanceToTarget <= BoundaryRange)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsCheckBoundary"), true);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}

		// Attack Section
		if (bAttackTime == true)
		{
			if (DistanceToTarget <= AttackRange)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}

}
