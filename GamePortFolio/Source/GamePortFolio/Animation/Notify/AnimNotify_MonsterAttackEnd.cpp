// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_MonsterAttackEnd.h"
#include "Character/AI/Monster/GHMonster.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UAnimNotify_MonsterAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AGHMonster* Monster = Cast<AGHMonster>(MeshComp->GetOwner());
	if (IsValid(Monster))
	{
		AAIController* AIController = Cast<AAIController>(Monster->GetController());
		UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent());
		BTComponent->GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttackEnd"), true);
	}
}
