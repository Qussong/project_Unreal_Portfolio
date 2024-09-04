// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTService_AttackTimer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"


UBTService_AttackTimer::UBTService_AttackTimer()
{
	NodeName = TEXT("AttackTimer");	// BT에 표시되는 노드의 이름 지정
	Interval = 1.f;
}

void UBTService_AttackTimer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 빙의된 Monster 객체가 있는지 확인
	MonsterPawn = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == MonsterPawn) return;

	// 빙의된 몬스터가 World 에 속해있는지 확인
	UWorld* World = MonsterPawn->GetWorld();
	if (nullptr == World) return;

	int32 AttackCoolTime = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("AttackCoolTime"));
	bool bAttackTime = OwnerComp.GetBlackboardComponent()->GetValueAsBool(FName("IsAttackTime"));

	if (bAttackTime) return;

	if (0 == AttackCoolTime)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsAttackTime"), true);
		// 사용할 공격 선택 + AttackRange 지정
		int32 AttackType = FMath::RandRange(1, 3);

		switch (AttackType)
		{
		case 1:
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("AttackType"), 1);
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName("AttackRange"), 400.f);
			break;
		}
		case 2 :
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("AttackType"), 2);
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName("AttackRange"), 300.f);
			break;
		}
		case 3:
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("AttackType"), 3);
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName("AttackRange"), 300.f);
			break;
		}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("AttackCoolTime"), --AttackCoolTime);
	}

}
