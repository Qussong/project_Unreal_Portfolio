// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotifyState_AttackLineTrace.h"
#include "Character/Player/GHPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"

void UAnimNotifyState_AttackLineTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	AGHPlayer* Player = Cast<AGHPlayer>(Owner);
	Player->AttackCheck_Begin(Start_V, End_V, Start_H, End_H);
}

void UAnimNotifyState_AttackLineTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	AGHPlayer* Player = Cast<AGHPlayer>(Owner);
	Player->AttackCheck_Tick(Start_V, End_V, Start_H, End_H);
}

void UAnimNotifyState_AttackLineTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
