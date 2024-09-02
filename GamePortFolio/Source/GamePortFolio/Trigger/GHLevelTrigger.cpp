// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/GHLevelTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Character/Player/GHPlayer.h"
#include "Kismet/GameplayStatics.h"

AGHLevelTrigger::AGHLevelTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGHLevelTrigger::OnOverlapBegin);
}

void AGHLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGHLevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGHLevelTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어 충돌시 이벤트 발생
	AGHPlayer* Player = Cast<AGHPlayer>(OtherActor);
	if (IsValid(Player))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}
}