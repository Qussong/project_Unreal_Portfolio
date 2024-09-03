// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_BackStep.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"

UBTTask_BackStep::UBTTask_BackStep()
{
	NodeName = TEXT("BackStep");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_BackStep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == Monster) return EBTNodeResult::Failed;

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	FVector TargetDirection = Target->GetActorLocation() - Monster->GetActorLocation();
	Monster->SetActorRotation(TargetDirection.Rotation());

	Monster->SetState(EMonsterState::BACKSTEP);
	return EBTNodeResult::InProgress;
}

void UBTTask_BackStep::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	bool bCheckBoundary = OwnerComp.GetBlackboardComponent()->GetValueAsBool(FName("IsCheckBoundary"));
	if (bCheckBoundary)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
