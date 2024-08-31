// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_Detect.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Character/AI/Monster/GHMonster.h"
#include "AIController.h"
#include "Character/AI/Monster/Normal/GHNormalMonster.h"

UBTTask_Detect::UBTTask_Detect()
{
	NodeName = TEXT("Detect");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Detect::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (IsValid(Monster))
	{
		Monster->SetState(EMonsterState::DETECT);

		// Normal Monster
		AGHNormalMonster* NormalMonster = Cast<AGHNormalMonster>(Monster);
		if (NormalMonster)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("Warniss"), EWarnissLevel::WARNING);
		}

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Type();
}

void UBTTask_Detect::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// Normal Monster
	int Warniss = OwnerComp.GetBlackboardComponent()->GetValueAsInt(TEXT("Warniss"));
	if (Warniss == EWarnissLevel::NORMAL)
	{
		// PreTarget 초기화
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("PreTarget"), nullptr);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (Warniss >= EWarnissLevel::DANGER)
	{
		// Target 설정
		UObject* PreTarget = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PreTarget"));
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), PreTarget);

		// 경계도 초기화
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("Warniss"), EWarnissLevel::NORMAL);
	}
}