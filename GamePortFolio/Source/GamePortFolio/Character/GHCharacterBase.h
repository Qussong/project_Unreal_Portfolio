// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GHCharacterBase.generated.h"

UCLASS()
class GAMEPORTFOLIO_API AGHCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGHCharacterBase();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Stat Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	TObjectPtr<class UGHBaseStatComponent> Stat;
};
