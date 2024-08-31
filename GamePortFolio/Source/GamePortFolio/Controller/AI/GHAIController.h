// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GHAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AGHAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;	// 컨트롤러가 특정 폰을 소유할 떄 호출
	virtual void OnUnPossess() override;

protected:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;

public:
	void RunAI();
	void StopAI();

// TeamSection
public:
	FORCEINLINE virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override
	{
		ETeamAttitude::Type Result = ETeamAttitude::Neutral;

		const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
		if (nullptr != OtherTeamAgent)
		{
			Result = OtherTeamAgent->GetGenericTeamId() == FGenericTeamId::NoTeam
				? ETeamAttitude::Neutral
				: FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherTeamAgent->GetGenericTeamId());
		}

		return Result;
	}

};
