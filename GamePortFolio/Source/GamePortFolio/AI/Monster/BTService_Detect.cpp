// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTService_Detect.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"
#include "Engine/OverlapResult.h"
#include "Controller/AI/GHAIController.h"
#include "Character/AI/Monster/Normal/GHNormalMonster.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");	// BT에 표시되는 노드의 이름 지정
	Interval = 1.f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 빙의된 Monster 객체가 있는지 확인
	MonsterPawn = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == MonsterPawn) return;

	// 빙의된 몬스터가 World 에 속해있는지 확인
	World = MonsterPawn->GetWorld();
	if (nullptr == World) return;

	// 주변 감지
	DetectTarget(OwnerComp);
}

void UBTService_Detect::DetectTarget(UBehaviorTreeComponent& OwnerComp)
{
	Center = MonsterPawn->GetActorLocation();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams ColliionQueryParma(SCENE_QUERY_STAT(Detact), false, MonsterPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECC_GameTraceChannel5,	// GHMonsterAction
		FCollisionShape::MakeSphere(DetectRadius),
		ColliionQueryParma);

	
	if (bResult)
	{
		// 충돌된 객체가 있는경우
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* DetectPawn = Cast<APawn>(OverlapResult.GetActor());
			AGHAIController* AIController = Cast<AGHAIController>(MonsterPawn->GetController());
			ETeamAttitude::Type RelationShip = AIController->GetTeamAttitudeTowards(*DetectPawn);

			UObject* PreTarget = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PreTarget"));

			// 이미 등록된 PreTarget 과 다르고 적군인경우 새로운 PreTarget 으로 등록
			if (PreTarget != DetectPawn
				&& RelationShip == ETeamAttitude::Hostile)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("PreTarget"), DetectPawn);
#if ENABLE_DRAW_DEBUG
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.5f);
				DrawDebugLine(World, Center, DetectPawn->GetActorLocation(), FColor::Red, false, 0.5f);
#endif
			}

			// Normal Monster
			AGHNormalMonster* NormalMonster = Cast<AGHNormalMonster>(MonsterPawn);
			EMonsterState NormalMonsterState = NormalMonster->GetState();
			if (NormalMonster
				&& EMonsterState::DETECT == NormalMonsterState
				&& RelationShip == ETeamAttitude::Hostile)
			{
				NormalMonster->IncreaseWarniss();
#if ENABLE_DRAW_DEBUG
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Yellow, false, 0.5f);
				DrawDebugLine(World, Center, DetectPawn->GetActorLocation(), FColor::Yellow, false, 0.5f);
#endif
				return;
			}
		}
	}

	// 현재 객체가 Normal Monster 이고 Detect 상태이며,
	// Detect 대상이 없는 경우
	AGHNormalMonster* NormalMonster = Cast<AGHNormalMonster>(MonsterPawn);
	if (NormalMonster
		&& EMonsterState::DETECT == MonsterPawn->GetState())
	{
		NormalMonster->DecreaseWarniss();
	}

#if ENABLE_DRAW_DEBUG
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.5f);
#endif
	
}
