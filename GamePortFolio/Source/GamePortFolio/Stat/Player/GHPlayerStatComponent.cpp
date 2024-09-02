// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/Player/GHPlayerStatComponent.h"
#include "Character/Player/GHPlayer.h"
#include "Math/UnrealMathUtility.h"

UGHPlayerStatComponent::UGHPlayerStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Stat Init Section
	MaxStamina = 100.f;
	CurrentStamina = MaxStamina;
	MaxMana = 100.f;
	CurrentMana = MaxMana;
	MaxEXP = 100.f;
	CurrentEXP = 0.f;

}

void UGHPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGHPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Stamina
	{
		// 순서 변경 x
		DecreaseStamina(DeltaTime);
		IncreaseStamina(DeltaTime);
	}
}

void UGHPlayerStatComponent::UseStamina(EStaminUseType UseType)
{
	FStatminaUsage Usage;

	if (EStaminUseType::RUN == UseType)
	{
		Usage.Continuous += (uint32)UseType;
	}

	if (EStaminUseType::ATTACK == UseType
		|| EStaminUseType::ROLL == UseType)
	{
		Usage.Once += (uint32)UseType;
	}

	StaminaUsage = Usage;
}

bool UGHPlayerStatComponent::CheckStamina(EStaminUseType UseType)
{
	if (EStaminUseType::RUN == UseType)
	{
		return 1.f <= CurrentStamina;
	}

	return (int32)UseType <= CurrentStamina;
}

void UGHPlayerStatComponent::DecreaseStamina(float DeltaTime)
{
	AGHPlayer* Owner = Cast<AGHPlayer>(GetOwner());
	if (!IsValid(Owner)) return;

	if (0 != StaminaUsage.Continuous
		|| 0 != StaminaUsage.Once)
	{
		// Stamina 사용량 반영
		CurrentStamina = FMath::Clamp(CurrentStamina - StaminaUsage.Continuous * DeltaTime, 0.f, MaxStamina);
		CurrentStamina = FMath::Clamp(CurrentStamina - StaminaUsage.Once, 0.f, MaxStamina);
		// Stamina 사용량 초기화
		StaminaUsage = {};
		// Stamina Widget 업데이트
		Owner->UpdateStaminaWidget();
	}
	else
	{
		bStaminaRecovery = true;
	}

}

void UGHPlayerStatComponent::IncreaseStamina(float DeltaTime)
{
	AGHPlayer* Owner = Cast<AGHPlayer>(GetOwner());
	if (!IsValid(Owner)) return;

	if (bStaminaRecovery)
	{
		// Stamina 사용량 반영
		CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRecoveryAmount * DeltaTime , 0.f, MaxStamina);
		bStaminaRecovery = false;
		// Stamina Widget 업데이트
		Owner->UpdateStaminaWidget();
	}
}
