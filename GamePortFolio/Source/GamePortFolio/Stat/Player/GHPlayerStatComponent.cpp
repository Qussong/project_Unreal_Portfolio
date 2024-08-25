// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/Player/GHPlayerStatComponent.h"

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
}

void UGHPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}
