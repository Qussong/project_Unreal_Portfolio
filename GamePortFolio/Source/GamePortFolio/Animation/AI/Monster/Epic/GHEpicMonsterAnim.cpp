// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AI/Monster/Epic/GHEpicMonsterAnim.h"

#include "Character/AI/Monster/GHMonster.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Character/AI/Monster/Epic/GHEpicMonster.h"
#include "GameFramework/CharacterMovementComponent.h"

UGHEpicMonsterAnim::UGHEpicMonsterAnim()
{
}

void UGHEpicMonsterAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UGHEpicMonsterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Boundary Section
	if (EMonsterAnimState::BOUNDARY == AnimState)
	{
		AGHEpicMonster* Owner = Cast<AGHEpicMonster>(TryGetPawnOwner());
		UBlackboardComponent* BBComp = Cast<AAIController>(Owner->GetController())->GetBlackboardComponent();

		FVector CurVelocity = Owner->GetMovementComponent()->Velocity;	// MoveDir
		CurVelocity.Z = 0.f;
		Speed = CurVelocity.Size();
		
		APawn* Target = Cast<APawn>(BBComp->GetValueAsObject(FName("Target")));
		FVector TargetDir = (Target->GetActorLocation() - Owner->GetActorLocation());	// ForwardDir
		TargetDir.Z = 0.f;
		float DotProduct = FVector::DotProduct(CurVelocity, TargetDir);
		float AngleRadian = FMath::Acos(DotProduct / (Speed * TargetDir.Size()));
		Direction = FMath::RadiansToDegrees(AngleRadian);
	}

}

void UGHEpicMonsterAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UGHEpicMonsterAnim::SetMonsterAnimState(EMonsterAnimState NewState)
{
	Super::SetMonsterAnimState(NewState);

	// ReadyFight Section
	if (EMonsterAnimState::WAIT == NewState)
	{
		// 몽타주 유효성 확인
		if (!IsValid(WaitMontage)) return;

		// 몽타주 재생중인지 확인
		if (Montage_IsPlaying(WaitMontage)) return;

		Montage_Play(WaitMontage);
	}

	// ReadyFight Section
	if (EMonsterAnimState::READYFIGHT == NewState)
	{
		// 몽타주 유효성 확인
		if (!IsValid(WaitMontage)) return;

		// 몽타주 재생중인지 확인
		if (Montage_IsPlaying(WaitMontage))
		{
			Montage_Play(WaitMontage);
			Montage_JumpToSection(FName("WaitEnd"), WaitMontage);
		}
	}
}
