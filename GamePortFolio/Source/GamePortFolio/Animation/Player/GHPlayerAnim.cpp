// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Player/GHPlayerAnim.h"
#include "Character/Player/GHPlayer.h"
#include "Controller/GHPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	if (Montage_IsPlaying(NormalAttackMontage)) return;

	// 플레이어 이동 중지
	Owner->GetCharacterMovement()->StopMovementImmediately();

	// 방향 설정
	Cast<AGHPlayerController>(Owner->GetController())->GetLocationUnderCursor();	// 마우스의 월드상의 위치 확인
	Cast<AGHPlayerController>(Owner->GetController())->Rotate();					// Player 회전

	// 몽타주 재생
	Montage_Play(NormalAttackMontage);
}

void UGHPlayerAnim::PlayKnockDownMontage()
{
	// 몽타주 유효성 확인
	if (!IsValid(KnockDownMontage)) return;

	// 몽타주 재생중인지 확인
	if (Montage_IsPlaying(KnockDownMontage)) return;

	// 플레이어 이동 중지
	Owner->GetCharacterMovement()->StopMovementImmediately();

	//
	Montage_Play(KnockDownMontage);
	FOnMontageEnded MontageEndedDelegate;
	MontageEndedDelegate.BindUObject(this, &UGHPlayerAnim::KnockDownMontageEnded);
	Montage_SetEndDelegate(MontageEndedDelegate, KnockDownMontage);
}

void UGHPlayerAnim::KnockDownMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Log, TEXT("KnockDown End"));
	Montage_Play(KnockDownMontage);
	Montage_JumpToSection(FName("KnockDownLoop"), KnockDownMontage);
}
