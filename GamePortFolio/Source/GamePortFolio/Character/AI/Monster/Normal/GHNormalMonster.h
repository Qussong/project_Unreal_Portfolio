// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AI/Monster/GHMonster.h"
#include "GHNormalMonster.generated.h"

enum EWarnissLevel : int32
{
	NORMAL = 0,
	WARNING = 3,
	DANGER = 6,
};

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHNormalMonster : public AGHMonster
{
	GENERATED_BODY()

public:
	AGHNormalMonster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

// Death Section
protected:
	virtual void SetDeath() override;

// Wariness State
private:
	UPROPERTY(VisibleAnywhere)
	int32 Warniss = EWarnissLevel::NORMAL;

// Team Section
public:
	int32 GetWarniss() { return Warniss; }
	FORCEINLINE void IncreaseWarniss() { Warniss += 1; }
	FORCEINLINE void DecreaseWarniss()
	{
		Warniss == EWarnissLevel::NORMAL ? Warniss = 0 : Warniss -= 1;
	}
	FORCEINLINE void DetectWarniss() { Warniss = EWarnissLevel::WARNING; }
	FORCEINLINE void ResetWarniss() { Warniss = EWarnissLevel::NORMAL; }

// UI Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<class UGHMonsterWidgetComponent> HUDWidgetComp;
protected:
	void UpdateHUD();

// Hit Section
protected:
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


};
