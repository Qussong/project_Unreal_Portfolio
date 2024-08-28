// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/GHEquipItem.h"
#include "GHArmor.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHArmor : public AGHEquipItem
{
	GENERATED_BODY()

public:
	AGHArmor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
