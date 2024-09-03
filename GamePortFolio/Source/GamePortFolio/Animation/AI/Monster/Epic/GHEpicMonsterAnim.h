// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AI/Monster/GHMonsterAnim.h"
#include "GHEpicMonsterAnim.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHEpicMonsterAnim : public UGHMonsterAnim
{
	GENERATED_BODY()
	
public:
	UGHEpicMonsterAnim();

public:
	virtual void NativeInitializeAnimation() override;					// 초기화
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	// 매 프레임 업데이트
	virtual void NativeBeginPlay() override;							// ABP 실제로 시작될 떄 한번 호출

protected:
	virtual void SetMonsterAnimState(EMonsterAnimState NewState) override;

// ReadyFight Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Death)
	TObjectPtr<UAnimMontage> WaitMontage;

// Boundary Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Boundary)
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Boundary)
	float Direction;

};
