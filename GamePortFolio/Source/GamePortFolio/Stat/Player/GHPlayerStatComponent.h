// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat/GHBaseStatComponent.h"
#include "GHPlayerStatComponent.generated.h"

UENUM()
enum class EStaminUseType : uint32
{
	RUN = 5,
	ATTACK = 8,
	ROLL = 10,
};

struct FStatminaUsage
{
	float Continuous = 0.f;
	float Once = 0.f;
};

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHPlayerStatComponent : public UGHBaseStatComponent
{
	GENERATED_BODY()
	
public:
	UGHPlayerStatComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Stamina Section
protected:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = Stamina)
	float CurrentStamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stamina)
	float MaxStamina;
public:
	FORCEINLINE float GetCurrentStamina() { return CurrentStamina; }
	FORCEINLINE float GetMaxStamina() { return MaxStamina; }
	void UseStamina(EStaminUseType UseType);
	bool CheckStamina(EStaminUseType UseType);
private:
	FStatminaUsage StaminaUsage;
	bool bStaminaRecovery = false;
	float StaminaRecoveryAmount = 5.f;
	void DecreaseStamina(float DeltaTime);
	void IncreaseStamina(float DeltaTime);

// Mana Section
protected:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = Mana)
	float CurrentMana;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mana)
	float MaxMana;
public:
	FORCEINLINE float GetCurrentMana() { return CurrentMana; }
	FORCEINLINE float GetMaxMana() { return MaxMana; }

// EXP Section
protected:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = EXP)
	float CurrentEXP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EXP)
	float MaxEXP;

public:
	FORCEINLINE float GetCurrentEXP() { return CurrentEXP; }
	FORCEINLINE float GetMaxEXP() { return MaxEXP; }

};
