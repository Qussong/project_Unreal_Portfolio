// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_BoundaryCheckEnd.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UAnimNotify_BoundaryCheckEnd : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_BoundaryCheckEnd();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
