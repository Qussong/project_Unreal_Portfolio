// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AI/GHAI.h"
#include "GHMonster.generated.h"

UENUM()
enum class EMonsterState : uint8
{
	// Common
	IDLE,
	TRACE,
	ATTACK,
	DEATH,
	ANGRY,
	HIT,
	// Normal
	DETECT,
};

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHMonster : public AGHAI
{
	GENERATED_BODY()
	
public:
	AGHMonster();

// Anim Section
protected:
	class UGHMonsterAnim* MonsterAnim;

// Death Section
protected:
	virtual void SetDeath() override;

// Monster State Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	EMonsterState MonsterState = EMonsterState::IDLE;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	EMonsterState MonsterPrevState = EMonsterState::IDLE;
public:
	virtual void SetState(EMonsterState NewState);
	FORCEINLINE EMonsterState GetState() { return MonsterState; }
	FORCEINLINE EMonsterState GetPrevState() { return MonsterPrevState; }

// UI Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<class UGHMonsterWidgetComponent> HUDWidgetComp;
protected:
	void UpdateHUD();
	
};
