// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AI/Monster/Epic/GHEpicMonsterController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

AGHEpicMonsterController::AGHEpicMonsterController()
{
	// BB Section
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		NormalMonsterBBRef(TEXT("/Script/AIModule.BlackboardData'/Game/Gihoon/AI/EpicMonster/BB_EpicMonster.BB_EpicMonster'"));
	if (NormalMonsterBBRef.Succeeded())
	{
		BBAsset = NormalMonsterBBRef.Object;
	}

	// BT Section
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		NormalMonsterBTRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Gihoon/AI/EpicMonster/BT_EpicMonster.BT_EpicMonster'"));
	if (NormalMonsterBTRef.Succeeded())
	{
		BTAsset = NormalMonsterBTRef.Object;
	}
}

void AGHEpicMonsterController::BeginPlay()
{
	Super::BeginPlay();
}

void AGHEpicMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGHEpicMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AGHEpicMonsterController::OnUnPossess()
{
	Super::OnUnPossess();

}
