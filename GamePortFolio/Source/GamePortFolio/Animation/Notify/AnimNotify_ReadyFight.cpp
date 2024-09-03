// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_ReadyFight.h"
#include "Character/AI/Monster/GHMonster.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UAnimNotify_ReadyFight::UAnimNotify_ReadyFight()
{

}

void UAnimNotify_ReadyFight::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AGHMonster* Monster = Cast<AGHMonster>(MeshComp->GetOwner());
	if (nullptr == Monster) return;

	AAIController* AIController = Cast<AAIController>(Monster->GetController());
	if (IsValid(AIController))
	{
		UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(AIController->BrainComponent);
		if (nullptr == BTComponent) return;

		BTComponent->GetBlackboardComponent()->SetValueAsBool(TEXT("IsReadyFight"), true);

	}
}
