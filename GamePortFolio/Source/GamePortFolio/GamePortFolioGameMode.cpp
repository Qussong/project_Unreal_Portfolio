// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamePortFolioGameMode.h"
#include "GamePortFolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGamePortFolioGameMode::AGamePortFolioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
