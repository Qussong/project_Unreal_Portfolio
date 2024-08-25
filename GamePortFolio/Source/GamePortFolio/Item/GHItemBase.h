// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GHItemBase.generated.h"

UCLASS()
class GAMEPORTFOLIO_API AGHItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AGHItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
