// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GHBaseTrigger.generated.h"

UCLASS()
class GAMEPORTFOLIO_API AGHBaseTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AGHBaseTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

// Trigger Box Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	class UBoxComponent* TriggerBox;
};
