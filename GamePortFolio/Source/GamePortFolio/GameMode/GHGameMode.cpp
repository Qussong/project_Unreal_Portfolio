// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GHGameMode.h"

AGHGameMode::AGHGameMode()
{
	// Default Pawn Section
	static ConstructorHelpers::FClassFinder<APawn>
		PlayerPawnClassRef(TEXT("/Game/Gihoon/Characters/Player/BP_GHPlayer.BP_GHPlayer_C"));
	if (PlayerPawnClassRef.Succeeded())
		DefaultPawnClass = PlayerPawnClassRef.Class;

	// Player Controller Section
	static ConstructorHelpers::FClassFinder<APlayerController>
		PlayerControllerClassRef(TEXT("/Game/Gihoon/Controller/Player/BP_GHPlayerController.BP_GHPlayerController_C"));
	if (PlayerControllerClassRef.Succeeded())
		PlayerControllerClass = PlayerControllerClassRef.Class;

}
