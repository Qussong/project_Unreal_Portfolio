// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger/GHBaseTrigger.h"
#include "GHLevelTrigger.generated.h"

UCLASS()
class GAMEPORTFOLIO_API AGHLevelTrigger : public AGHBaseTrigger
{
	GENERATED_BODY()
	
public:	
	AGHLevelTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

// Level Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelName)
	FName LevelName;

// Ovelap Event Section
protected:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
