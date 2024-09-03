// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTDecorator_Boundary.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"
#include "BehaviorTree/BlackBoardComponent.h"

UBTDecorator_Boundary::UBTDecorator_Boundary()
{
	NodeName = TEXT("IsClose");
}

bool UBTDecorator_Boundary::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// 빙의한 Pawn 객체가 Monster 가 맞는지 확인
	AGHMonster* MonsterPawn = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == MonsterPawn) return false;

	// Target 이 존재하는지 확인
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (nullptr == Target) return false;

	// 공격 타이밍이 아닌지 확인
	bool AttackTime = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsAttackTime"));
	if (AttackTime) return false;

	float DistanceToTarget = MonsterPawn->GetDistanceTo(Target);	// Target 과 Monster 사이의 거리

	return (DistanceToTarget <= BoundartDistance);
}
