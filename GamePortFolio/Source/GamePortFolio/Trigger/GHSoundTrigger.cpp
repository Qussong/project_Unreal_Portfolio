// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/GHSoundTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Character/Player/GHPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/GHGameMode_Play.h"

AGHSoundTrigger::AGHSoundTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGHSoundTrigger::OnOverlapBegin);
}

void AGHSoundTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void AGHSoundTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGHSoundTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	if (nullptr == GameMode) return;

	AGHGameMode_Play* GameModePlay = Cast<AGHGameMode_Play>(GameMode);
	if (IsValid(GameModePlay))
	{
		GameModePlay->PlayBattleBGM();
		Destroy();
	}
}
