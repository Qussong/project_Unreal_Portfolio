// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_Boundary.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"


UBTTask_Boundary::UBTTask_Boundary()
{
	NodeName = TEXT("Boundary");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Boundary::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == Monster) return EBTNodeResult::Failed;

	Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	if (nullptr == Target) return EBTNodeResult::Failed;

	Monster->SetState(EMonsterState::BOUNDARY);
	return EBTNodeResult::InProgress;
}

void UBTTask_Boundary::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FVector TargetLocation = Target->GetActorLocation();
	FVector MonsterLocation = Monster->GetActorLocation();

	FVector MtoPDir = (TargetLocation - MonsterLocation).GetSafeNormal();
	FVector VectorZ(0.0f, 0.0f, 1.0f); // ZÃà ¹æÇâ º¤ÅÍ

	FVector CrossProduct = FVector::CrossProduct(VectorZ, MtoPDir).GetSafeNormal();

	Monster->AddMovementInput(CrossProduct, BoundarySpeed * DeltaSeconds, false);
	Monster->SetActorRotation(FRotationMatrix::MakeFromX(MtoPDir).Rotator());
}
