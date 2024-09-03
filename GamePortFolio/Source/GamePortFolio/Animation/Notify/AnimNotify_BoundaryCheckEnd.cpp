// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_BoundaryCheckEnd.h"
#include "Character/AI/Monster/GHMonster.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UAnimNotify_BoundaryCheckEnd::UAnimNotify_BoundaryCheckEnd()
{
}

void UAnimNotify_BoundaryCheckEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AGHMonster* Monster = Cast<AGHMonster>(MeshComp->GetOwner());
	if (nullptr == Monster) return;

	AAIController* AIController = Cast<AAIController>(Monster->GetController());
	if (nullptr == AIController) return;

	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(AIController->BrainComponent);
	if (BTComponent)
	{
		BTComponent->GetBlackboardComponent()->SetValueAsBool(TEXT("IsCheckBoundary"), true);
	}
}
