// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_Angry.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"

UBTTask_Angry::UBTTask_Angry()
{
	NodeName = TEXT("Angry");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Angry::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->SetState(EMonsterState::ANGRY);

	return EBTNodeResult::InProgress;
}

void UBTTask_Angry::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	bool isAngryEnd = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsAngryEnd"));
	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target"));

	if (isAngryEnd)
	{
		if (Target)
		{
			// Target 이 있는 경우
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		else
		{
			// Target 이 없는 경우
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsAngryEnd"), false);
	}

}
