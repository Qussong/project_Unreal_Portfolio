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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float MaxHealth;
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float CurrentHealth = MaxHealth;
private:
	FORCEINLINE void SetCurrentHealth(float NewCurHealth) { CurrentHealth = NewCurHealth; }
public:
	FORCEINLINE void SetMaxHealth(float NewMaxHealth) 
	{ 
		MaxHealth = NewMaxHealth; 
		SetCurrentHealth(NewMaxHealth);
	}
	FORCEINLINE float GetCurrnetHealth() { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	float IncreaeHealth(float Heal);
	float DecreaseHealth(float Damage);

// EXP Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EXP)
	int32 Level;
public:
	FORCEINLINE void SetLevel(int32 NewLevel) { Level = NewLevel; }
	FORCEINLINE float GetLevel() { return Level; }
	FORCEINLINE float UpLevel() { return ++Level; }

// ATK Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ATK)
	float ATK;
public:
	FORCEINLINE float GetATK() { return ATK; }
	FORCEINLINE void SetATK(float NewATK) { ATK = NewATK; }
	FORCEINLINE float IncreaseATK(float Point) { ATK += Point; return ATK; }

// DEF Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DEF)
	float DEF;
public:
	FORCEINLINE float GetDEF() { return DEF; }
	FORCEINLINE void SetDEF(float NewDEF) { DEF = NewDEF; }
	FORCEINLINE float IncreaseDEF(float Point) { DEF += Point; return DEF; }
};
