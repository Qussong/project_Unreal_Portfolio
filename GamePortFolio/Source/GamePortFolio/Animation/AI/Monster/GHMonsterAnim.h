// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AI/GHAIAnim.h"
#include "GHMonsterAnim.generated.h"

UENUM(BlueprintType)
enum class EMonsterAnimState : uint8
{
	// Common
	IDLE,
	WALK,
	RUN,
	ATTACK,
	ATTACK2,
	DEATH,
	DEATH2,
	ANGRY,
	HIT,
	// Normal
	DETECT,
};

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHMonsterAnim : public UGHAIAnim
{
	GENERATED_BODY()
	
public:
	UGHMonsterAnim();

public:
	virtual void NativeInitializeAnimation() override;					// 초기화
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	// 매 프레임 업데이트
	virtual void NativeBeginPlay() override;							// ABP 실제로 시작될 떄 한번 호출

	// Anim State Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	EMonsterAnimState AnimState = EMonsterAnimState::IDLE;
public:
	FORCEINLINE EMonsterAnimState GetMonsterAnimState() { return AnimState; }
	FORCEINLINE void SetMonsterAnimState(EMonsterAnimState NewState) { AnimState = NewState; }
};
