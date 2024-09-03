// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster/BTTask_Attack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "Character/AI/Monster/GHMonster.h"

#include "Character/AI/Monster/Normal/GHNormalMonster.h"
#include "Character/AI/Monster/Epic/GHEpicMonster.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = OwnerComp.GetAIOwner()->GetPawn<AGHMonster>();
	if (nullptr == Monster) return EBTNodeResult::Failed;

	Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	Normal = Cast<AGHNormalMonster>(Monster);
	Epic = Cast<AGHEpicMonster>(Monster);

	//Normal Monster Section
	if (IsValid(Normal))
	{	
		Monster->SetState(EMonsterState::ATTACK);
	}

	//Epic Monster Section
	if (IsValid(Epic))
	{
		int32 AttackType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(TEXT("AttackType"));
		switch (AttackType)
		{
		case 1 : 
			Monster->SetState(EMonsterState::ATTACK);
			break;
		case 2 :
			Monster->SetState(EMonsterState::ATTACK2);
			break;
		case 3 :
			Monster->SetState(EMonsterState::ATTACK3);
			break;
		}

		if (AttackType != 1)
		{
			FVector TargetDirection = Target->GetActorLocation() - Monster->GetActorLocation();
			TargetDirection.Z = 0.f;
			TargetRotation = FRotationMatrix::MakeFromX(TargetDirection).Rotator();
		}
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	bool IsAttackEnd = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsAttackEnd"));

	//Normal Monster Section
	if (IsValid(Normal))
	{
		if (IsAttackEnd)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttackEnd"), false);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

	//Epic Monster Section
	if (IsValid(Epic))
	{
		int AttackType = OwnerComp.GetBlackboardComponent()->GetValueAsInt(TEXT("AttackType"));
		if (AttackType != 1)
		{
			FRotator CurRotation = Monster->GetActorRotation();
			FRotator NewRotation = FMath::RInterpTo(CurRotation, TargetRotation, DeltaSeconds, 10.0f);
			Monster->SetActorRotation(NewRotation);
		}

		if (IsAttackEnd)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttackEnd"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttackTime"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("AttackCoolTime"), 2);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsCheckBoundary"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("AttackType"), 0);

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}