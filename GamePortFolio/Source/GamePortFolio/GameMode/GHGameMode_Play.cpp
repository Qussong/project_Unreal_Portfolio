// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GHGameMode_Play.h"

#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

AGHGameMode_Play::AGHGameMode_Play()
{
	// Default Pawn Section
	static ConstructorHelpers::FClassFinder<APawn>
		PlayerPawnClassRef(TEXT("/Game/Gihoon/Characters/Player/BPC_GHPlayer.BPC_GHPlayer_C"));
	if (PlayerPawnClassRef.Succeeded())
	{
		DefaultPawnClass = PlayerPawnClassRef.Class;
	}

	// Player Controller Section
	static ConstructorHelpers::FClassFinder<APlayerController>
		PlayerControllerClassRef(TEXT("/Game/Gihoon/Controller/Player/BP_GHPlayerController.BP_GHPlayerController_C"));
	if (PlayerControllerClassRef.Succeeded())
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	// BGM Section
	static ConstructorHelpers::FObjectFinder<USoundBase>
		BGM_Level01Ref(TEXT("/Script/Engine.SoundCue'/Game/Gihoon/Sound/Respawn_Cue.Respawn_Cue'"));
	if (BGM_Level01Ref.Succeeded())
	{
		BGM_Level01 = BGM_Level01Ref.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> 
		BGM_Level02Ref(TEXT("/Script/Engine.SoundCue'/Game/Gihoon/Sound/HeavyRain_Cue.HeavyRain_Cue'"));
	if (BGM_Level02Ref.Succeeded())
	{
		BGM_Level02_Rain = BGM_Level02Ref.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase>
		BGM_Level02_BattleRef(TEXT("/Script/Engine.SoundCue'/Game/Gihoon/Sound/Battle_Cue.Battle_Cue'"));
	if (BGM_Level02_BattleRef.Succeeded())
	{
		BGM_Level02_Battle = BGM_Level02_BattleRef.Object;
	}
}

void AGHGameMode_Play::BeginPlay()
{
	Super::BeginPlay();

	FString LevelName = UGameplayStatics::GetCurrentLevelName(this, true);
	
	if (FName("Level_01") == LevelName
		&& IsValid(BGM_Level01))
	{
		UGameplayStatics::PlaySound2D(this, BGM_Level01);
	}

	if (FName("Level_02") == LevelName
		&& IsValid(BGM_Level02_Rain))
	{
		UGameplayStatics::PlaySound2D(this, BGM_Level02_Rain);
	}

}

void AGHGameMode_Play::PlayBattleBGM()
{
	if (IsValid(BGM_Level02_Battle))
	{
		UGameplayStatics::PlaySound2D(this, BGM_Level02_Battle);
	}
}
