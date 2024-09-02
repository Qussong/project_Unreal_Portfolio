// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AI/Monster/GHMonster.h"
#include "GHEpicMonster.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHEpicMonster : public AGHMonster
{
	GENERATED_BODY()
	
public:
	AGHEpicMonster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
