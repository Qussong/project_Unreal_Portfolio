// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_TurnToTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (nullptr == TargetPawn)
		return EBTNodeResult::Failed;

	FVector TargetDirection = TargetPawn->GetActorLocation() - Monster->GetActorLocation();
	TargetDirection.Z = 0.f;
	TargetRotation = FRotationMatrix::MakeFromX(TargetDirection).Rotator();

	return EBTNodeResult::InProgress;
}

void UBTTask_TurnToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FRotator CurRotation = Monster->GetActorRotation();
	FRotator NewRotation = FMath::RInterpTo(CurRotation, TargetRotation, DeltaSeconds, 10.0f);
	Monster->SetActorRotation(NewRotation);

	float Tolerance = 1.0f; // 허용 오차 값 (1도 정도로 설정)
	if (FMath::Abs(TargetRotation.Pitch - CurRotation.Pitch) <= Tolerance
		&& FMath::Abs(TargetRotation.Yaw - CurRotation.Yaw) <= Tolerance
		&& FMath::Abs(TargetRotation.Roll - CurRotation.Roll) <= Tolerance)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
