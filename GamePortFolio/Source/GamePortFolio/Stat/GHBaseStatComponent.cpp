
#include "Stat/GHBaseStatComponent.h"

UGHBaseStatComponent::UGHBaseStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Stat Init Section
	MaxHealth = 150.f;
	CurrentHealth = MaxHealth;
	Level = 1;
	ATK = 10;
	DEF = 10;
}


void UGHBaseStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UGHBaseStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

