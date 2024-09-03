// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ReadyFight.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UAnimNotify_ReadyFight : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_ReadyFight();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);


};
