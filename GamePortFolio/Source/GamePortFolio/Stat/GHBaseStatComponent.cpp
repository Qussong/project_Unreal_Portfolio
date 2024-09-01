
#include "Stat/GHBaseStatComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Character/GHCharacterBase.h"

UGHBaseStatComponent::UGHBaseStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Stat Init Section
	SetMaxHealth(100.f);
	SetLevel(1);
	SetATK(10.f);
	SetDEF(10.f);
}

void UGHBaseStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGHBaseStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float UGHBaseStatComponent::IncreaeHealth(float Heal)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Heal, 0.f, MaxHealth);

	return CurrentHealth;
}

float UGHBaseStatComponent::DecreaseHealth(float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);

	// »ç¸ÁÃ³¸®
	if (0.f >= CurrentHealth)
	{
		Cast<AGHCharacterBase>(GetOwner())->SetDeath();
	}

	return CurrentHealth;
}

