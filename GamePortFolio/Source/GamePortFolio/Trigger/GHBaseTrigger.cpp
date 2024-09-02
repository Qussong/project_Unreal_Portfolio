
#include "Trigger/GHBaseTrigger.h"
#include "Components/BoxComponent.h"

AGHBaseTrigger::AGHBaseTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	// Trigger Box Section
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->InitBoxExtent(FVector(200.0f, 200.0f, 100.0f));

}

void AGHBaseTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGHBaseTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

