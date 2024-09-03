// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_Idle.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"

#include "Character/AI/Monster/Normal/GHNormalMonster.h"
#include "Character/AI/Monster/Epic/GHEpicMonster.h"

UBTTask_Idle::UBTTask_Idle()
{
	NodeName = TEXT("Idle");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Mosnter Anim Section
	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (IsValid(Monster))
	{
		if (nullptr != Cast<AGHNormalMonster>(Monster))
			Monster->SetState(EMonsterState::IDLE);

		if (nullptr != Cast<AGHEpicMonster>(Monster))
			Monster->SetState(EMonsterState::WAIT);

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

