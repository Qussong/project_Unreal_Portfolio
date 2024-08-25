// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GHBaseStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPORTFOLIO_API UGHBaseStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGHBaseStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Health Section
protected:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float CurrentHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float MaxHealth;
public:
	FORCEINLINE float GetCurrnetHealth() { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float IncreaeHealth(float Heal)
	{
		CurrentHealth = MaxHealth - CurrentHealth < Heal ? MaxHealth : CurrentHealth + Heal;
		return CurrentHealth;
	}
	FORCEINLINE float DecreaseHealth(float Damage) { CurrentHealth -= Damage; return CurrentHealth; }

// EXP Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EXP)
	int32 Level;
public:
	FORCEINLINE float GetLevel() { return Level; }
	FORCEINLINE float UpLevel() { return ++Level; }

// ATK Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ATK)
	float ATK;
public:
	FORCEINLINE float GetATK() { return ATK; }
	FORCEINLINE float IncreaseATK(float Point) { ATK += Point; return ATK; }

// DEF Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DEF)
	float DEF;
public:
	FORCEINLINE float GetDEF() { return DEF; }
	FORCEINLINE float IncreaseDEF(float Point) { DEF += Point; return DEF; }
};
