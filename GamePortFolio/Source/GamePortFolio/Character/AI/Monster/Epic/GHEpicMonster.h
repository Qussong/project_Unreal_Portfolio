// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AI/Monster/GHMonster.h"
#include "GHEpicMonster.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHEpicMonster : public AGHMonster
{
	GENERATED_BODY()
	
public:
	AGHEpicMonster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

// Death Section
protected:
	virtual void SetDeath() override;

// Hit Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hit)
	TSet<AActor*> HitCheckContainer;
protected:
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

// Weapon Section
protected:
	TObjectPtr<UChildActorComponent> WeaponActorComp;
	TObjectPtr<UStaticMesh> SwordMesh;
public:
	UChildActorComponent* GetWeaponComp() { return WeaponActorComp; }

// Attack Section
public:
	void AttackCheck_Begin(FVector& Start_V, FVector End_V, FVector& Start_H, FVector& End_H);
	void AttackCheck_Tick(FVector& Start_V, FVector End_V, FVector& Start_H, FVector& End_H);
	void EnemyHit(TArray<FHitResult>& HitResults);

	FVector Attack2Center;
	float Attack2Radius = 20.f;
	void AttackCheck_Begin2();
	void AttackCheck_Tick2();
	void Hit(TArray<AActor*>& HitResults);
};
