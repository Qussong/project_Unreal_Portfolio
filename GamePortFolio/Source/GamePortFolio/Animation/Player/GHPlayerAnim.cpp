// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Player/GHPlayerAnim.h"
#include "Character/Player/GHPlayer.h"
#include "Controller/GHPlayerController.h"
#include "Stat/Player/GHPlayerStatComponent.h"

UGHPlayerAnim::UGHPlayerAnim()
{
}

void UGHPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UGHPlayerAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner = Cast<AGHPlayer>(TryGetPawnOwner());
}

void UGHPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UGHPlayerAnim::PlayNormalAttackMontage()
{
	// 몽타주 유효성 확인
	if (!IsValid(NormalAttackMontage)) return;

	// 몽타주 재생중인지 확인
	if (Montage_IsPlaying(NormalAttackMontage) && !bComboAttack) return;

	// 스태미나 소모
	Cast<UGHPlayerStatComponent>(Owner->GetStat())->UseStamina(EStaminUseType::ATTACK);

	// 방향 설정
	Cast<AGHPlayerController>(Owner->GetController())->GetLocationUnderCursor();	// 마우스의 월드상의 위치 확인
	Cast<AGHPlayerController>(Owner->GetController())->Rotate();					// Player 회전

	// 몽타주 재생
	if (bComboAttack)
	{
		++ComboAttackSection %= 3;
		Montage_Stop(0.2f, NormalAttackMontage);
		Montage_Play(NormalAttackMontage);
		Montage_Play(NormalAttackMontage);
		Montage_JumpToSection(ComboAttackSectionArray[ComboAttackSection]);
	}
	else
	{
		ComboAttackSection = 0;
		Montage_Play(NormalAttackMontage);
	}
}

void UGHPlayerAnim::PlayKnockDownMontage()
{
	// 몽타주 유효성 확인
	if (!IsValid(KnockDownMontage)) return;

	// 몽타주 재생중인지 확인
	if (Montage_IsPlaying(KnockDownMontage)) return;

	Montage_Play(KnockDownMontage);
}

void UGHPlayerAnim::PlayDeathMontage()
{
	// 몽타주 유효성 확인
	if (!IsValid(KnockDownMontage)) return;

	// 몽타주 재생중인지 확인
	if (Montage_IsPlaying(KnockDownMontage))
	{
		Montage_Stop(0.2f);
		Montage_Play(KnockDownMontage);
		Montage_JumpToSection(FName("KnockDownDead"));

		SetWhenStopMontage(1.6f); // 1.6f 초 후에 Montage 업데이트 정지
	}
}

void UGHPlayerAnim::SetWhenStopMontage(float CallTime)
{
	float TimeToTrigger = CallTime;
	FTimerHandle EndTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		EndTimerHandle, this, &UGHPlayerAnim::MontageStop, TimeToTrigger, false);
}

void UGHPlayerAnim::MontageStop()
{
	// 애니메이션의 업데이트를 일시적으로 중단
	GetOwningComponent()->bPauseAnims = true;
}

void UGHPlayerAnim::PlayRollMontage()
{
	// 몽타주 유효성 확인
	if (!IsValid(RollMontage)) return;

	// 몽타주 재생중인지 확인
	if (Montage_IsPlaying(RollMontage)) return;

	// 플레이어 이동 (Timeline)
	Cast<AGHPlayer>(Owner)->StartRollTimeline();

	Montage_Play(RollMontage);
	if (Owner->GetIsEquip())
	{
		Montage_JumpToSection(FName("CombatRoll"));
	}

}