// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/GHEquipItem.h"
#include "GHWeapon.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHWeapon : public AGHEquipItem
{
	GENERATED_BODY()
	
public:
	AGHWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
