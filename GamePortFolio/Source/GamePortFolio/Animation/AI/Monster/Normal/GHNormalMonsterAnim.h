// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AI/Monster/GHMonsterAnim.h"
#include "GHNormalMonsterAnim.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHNormalMonsterAnim : public UGHMonsterAnim
{
	GENERATED_BODY()
	
public:
	UGHNormalMonsterAnim();

public:
	virtual void NativeInitializeAnimation() override;					// 초기화
	virtual void NativeBeginPlay() override;							// ABP 실제로 시작될 떄 한번 호출
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	// 매 프레임 업데이트

};
