// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotifyState_RecoveryCancel.h"
#include "Character/Player/GHPlayer.h"
#include "EnhancedInputComponent.h"
#include "Animation/Player/GHPlayerAnim.h"

void UAnimNotifyState_RecoveryCancel::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UAnimNotifyState_RecoveryCancel::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	AGHPlayer* Player = Cast<AGHPlayer>(Owner);
	FEnhancedInputActionValueBinding* MoveInput = Player->GetMoveActionValue();

	bool IsMove = MoveInput->GetValue().Get<bool>();
	if (IsMove)
	{
		UAnimInstance* Anim = MeshComp->GetAnimInstance();
		if (nullptr == Anim) return;

		UAnimMontage* NormalAttackMontage = Cast<UGHPlayerAnim>(Anim)->GetNormalAttackMontage();
		if (nullptr == NormalAttackMontage) return;

		if (Anim->Montage_IsPlaying(NormalAttackMontage))
		{
			Anim->Montage_Stop(0.2f, NormalAttackMontage);
		}
	}
}

void UAnimNotifyState_RecoveryCancel::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
