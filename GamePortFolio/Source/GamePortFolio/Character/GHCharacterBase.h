// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "GHCharacterBase.generated.h"

enum ETeamID : uint8
{
	PLAYER = 1,
	MONSTER = 2,
	NOTEAM = 255,
};

UCLASS()
class GAMEPORTFOLIO_API AGHCharacterBase : public ACharacter
										 , public IGenericTeamAgentInterface
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

// Team Section
protected:
	UPROPERTY(VisibleAnywhere)
	uint8 TeamID = (uint8)FGenericTeamId::NoTeam;	// = 255
	FORCEINLINE void SetTeamID(uint8 NewTeamID) { TeamID = NewTeamID; }
public:
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }

// Hit Section
protected:
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

// Death Section
public:
	virtual void SetDeath() {};
};
