// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AttackLineTrace.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UAnimNotifyState_AttackLineTrace : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	TObjectPtr<class AGHPlayer> Player;
	TObjectPtr<class AGHEpicMonster> Epic;

protected:
	FVector Start_V;
	FVector End_V;

	FVector Start_H;
	FVector End_H;
};
	
