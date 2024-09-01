// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotifyState_SphereOverlap.h"
#include "Character/AI/Monster/Normal/GHNormalMonster.h"

void UAnimNotifyState_SphereOverlap::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	AGHNormalMonster* NormalMonster = Cast<AGHNormalMonster>(Owner);
	if (IsValid(NormalMonster))
	{
		NormalMonster->AttackCheck_Begin();
	}
}

void UAnimNotifyState_SphereOverlap::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	AGHNormalMonster* NormalMonster = Cast<AGHNormalMonster>(Owner);
	if (IsValid(NormalMonster))
	{
		NormalMonster->AttackCheck_Tick();
	}
}