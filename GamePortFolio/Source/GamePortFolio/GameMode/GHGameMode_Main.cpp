// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GHGameMode_Main.h"
#include "Character/ETC/GHMainLevelCharacter.h"

#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

AGHGameMode_Main::AGHGameMode_Main()
{
	// Default Pawn Section
	DefaultPawnClass = AGHMainLevelCharacter::StaticClass();

	// Player Controller Section
	static ConstructorHelpers::FClassFinder<APlayerController>
		PlayerControllerClassRef(TEXT("/Game/Gihoon/Controller/Player/BP_GHPlayerController.BP_GHPlayerController_C"));
	if (PlayerControllerClassRef.Succeeded())
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	// BGM Section
	static ConstructorHelpers::FObjectFinder<USoundBase>
		BGM_MainRef(TEXT(""));
	if (BGM_MainRef.Succeeded())
	{
		BGM_Main = BGM_MainRef.Object;
	}
}

void AGHGameMode_Main::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BGM_Main))
	{
		UGameplayStatics::PlaySound2D(this, BGM_Main);
	}
}
