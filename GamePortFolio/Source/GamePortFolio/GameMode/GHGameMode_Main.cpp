// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GHGameMode_Main.h"
#include "Character/ETC/GHMainLevelCharacter.h"

AGHGameMode_Main::AGHGameMode_Main()
{
	// Default Pawn Section
	DefaultPawnClass = AGHMainLevelCharacter::StaticClass();

	// Player Controller Section
	static ConstructorHelpers::FClassFinder<APlayerController>
		PlayerControllerClassRef(TEXT("/Game/Gihoon/Controller/Player/BP_GHPlayerController.BP_GHPlayerController_C"));
	if (PlayerControllerClassRef.Succeeded())
		PlayerControllerClass = PlayerControllerClassRef.Class;
}
