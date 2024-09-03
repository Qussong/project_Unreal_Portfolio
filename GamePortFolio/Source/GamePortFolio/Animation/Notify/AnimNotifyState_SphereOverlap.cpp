// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotifyState_SphereOverlap.h"
#include "Character/AI/Monster/Normal/GHNormalMonster.h"
#include "Character/AI/Monster/Epic/GHEpicMonster.h"

void UAnimNotifyState_SphereOverlap::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	Normal = Cast<AGHNormalMonster>(Owner);
	Epic = Cast<AGHEpicMonster>(Owner);

	if (IsValid(Normal))
	{
		Normal->AttackCheck_Begin();
	}
	if (IsValid(Epic))
	{
		Epic->AttackCheck_Begin2();
	}
}

void UAnimNotifyState_SphereOverlap::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (IsValid(Normal))
	{
		Normal->AttackCheck_Tick();
	}

	if (IsValid(Epic))
	{
		Epic->AttackCheck_Tick2();
	}
}