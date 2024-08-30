// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AI/Monster/GHMonster.h"
#include "GHNormalMonster.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHNormalMonster : public AGHMonster
{
	GENERATED_BODY()

public:
	AGHNormalMonster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
