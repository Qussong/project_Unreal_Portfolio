// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AI/GHAIController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AGHAIController::AGHAIController()
{
}

void AGHAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AGHAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGHAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void AGHAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AGHAIController::RunAI()
{
	if (IsValid(BBAsset) && IsValid(BTAsset))
	{
		UBlackboardComponent* BBPtr = Blackboard.Get();	// AI Controller 에서 기본적으로 제공되는 변수(Blackboard)
		bool isInitBB = UseBlackboard(BBAsset, BBPtr);	// BB 초기화
		if (isInitBB)
		{
			bool BTRunResult = RunBehaviorTree(BTAsset);// BT 구동
			ensure(BTRunResult);
		}
	}
}

void AGHAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();	// 안전하게 종료한다는 인자가 기본값으로 들어가 있다. (EBTStopMode::Safe)
	}
}
