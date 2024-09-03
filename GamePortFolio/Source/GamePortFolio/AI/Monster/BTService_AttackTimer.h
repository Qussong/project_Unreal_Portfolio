// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AttackTimer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UBTService_AttackTimer : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_AttackTimer();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	TObjectPtr<class AGHMonster> MonsterPawn;

};
