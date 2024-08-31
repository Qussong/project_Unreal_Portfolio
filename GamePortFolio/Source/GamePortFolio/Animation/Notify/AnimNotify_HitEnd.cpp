// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_HitEnd.h"
#include "Character/AI/Monster/GHMonster.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UAnimNotify_HitEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AGHMonster* Monster = Cast<AGHMonster>(MeshComp->GetOwner());
	if (Monster)
	{
		AAIController* AIController = Cast<AAIController>(Monster->GetController());
		if (AIController)
		{
			UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(AIController->BrainComponent);
			if (BTComponent)
			{
				BTComponent->GetBlackboardComponent()->SetValueAsBool(TEXT("IsHit"), false);
			}
		}
	}
}
