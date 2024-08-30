// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AI/Monster/Normal/GHNormalMonsterController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

AGHNormalMonsterController::AGHNormalMonsterController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		NormalMonsterBBRef(TEXT("/Script/AIModule.BlackboardData'/Game/Gihoon/AI/NormalMonster/BB_NormalMonster.BB_NormalMonster'"));
	if (NormalMonsterBBRef.Succeeded())
	{
		BBAsset = NormalMonsterBBRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		NormalMonsterBTRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Gihoon/AI/NormalMonster/BT_NormalMonster.BT_NormalMonster'"));
	if (NormalMonsterBTRef.Succeeded())
	{
		BTAsset = NormalMonsterBTRef.Object;
	}

}

void AGHNormalMonsterController::BeginPlay()
{
	Super::BeginPlay();
}

void AGHNormalMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGHNormalMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AGHNormalMonsterController::OnUnPossess()
{
	Super::OnUnPossess();
}
