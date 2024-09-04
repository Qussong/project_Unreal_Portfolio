// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/GHGameMode.h"
#include "GHGameMode_Play.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHGameMode_Play : public AGHGameMode
{
	GENERATED_BODY()
	
public:
	AGHGameMode_Play();

public:
	virtual void BeginPlay() override;

// BGM Section
private:
	TObjectPtr<class USoundBase> BGM_Level01;
	TObjectPtr<class USoundBase> BGM_Level02_Rain;
	TObjectPtr<class USoundBase> BGM_Level02_Battle;

public:
	void PlayBattleBGM();
};
