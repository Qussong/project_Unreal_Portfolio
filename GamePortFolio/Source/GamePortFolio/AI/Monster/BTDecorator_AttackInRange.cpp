// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTDecorator_AttackInRange.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Character/AI/Monster/Normal/GHNormalMonster.h"
#include "Character/AI/Monster/Epic/GHEpicMonster.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	bool bResult = false;

	// 빙의한 Pawn 객체가 Monster 가 맞는지 확인
	AGHMonster* MonsterPawn = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == MonsterPawn) return false;

	// Target 이 존재하는지 확인
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (nullptr == Target) return false;

	float DistanceToTarget = MonsterPawn->GetDistanceTo(Target);	// Target 과 Monster 사이의 거리

	AGHNormalMonster* Normal = Cast<AGHNormalMonster>(MonsterPawn);
	if (IsValid(Normal))
	{
		bResult = (DistanceToTarget <= NomalAttackRange);
	}

	AGHEpicMonster* Epic = Cast<AGHEpicMonster>(MonsterPawn);
	if (IsValid(Epic))
	{
		float EpicAttackRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName("AttackRange"));
		bResult = (DistanceToTarget <= EpicAttackRange);
	}

	return bResult;
}
