// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AI/Monster/Normal/GHNormalMonsterController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

AGHNormalMonsterController::AGHNormalMonsterController()
{
	// BB Section
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		NormalMonsterBBRef(TEXT("/Script/AIModule.BlackboardData'/Game/Gihoon/AI/NormalMonster/BB_NormalMonster.BB_NormalMonster'"));
	if (NormalMonsterBBRef.Succeeded())
	{
		BBAsset = NormalMonsterBBRef.Object;
	}

	// BT Section
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		NormalMonsterBTRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Gihoon/AI/NormalMonster/BT_NormalMonster.BT_NormalMonster'"));
	if (NormalMonsterBTRef.Succeeded())
	{
		BTAsset = NormalMonsterBTRef.Object;
	}

	// Perception Section
	MonsterPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("MonsterPerception"));
	SetPerceptionComponent(*MonsterPerception);	// AIController 는 Perception 을 등록할 수 있다.

	// SenseConfig_Sight Section
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("MonsterSight"));
	SightConfig->SightRadius = 800.f;
	SightConfig->LoseSightRadius = 1200.f;
	SightConfig->PeripheralVisionAngleDegrees = 45.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 1000.f;

	// Sight Sense 등록 (감각기관 배열에 추가)
	MonsterPerception->ConfigureSense(*SightConfig);

	// 대표 감각기관 설정
	MonsterPerception->SetDominantSense(SightConfig->GetSenseImplementation());

}

void AGHNormalMonsterController::BeginPlay()
{
	Super::BeginPlay();

	// Target 이 갱신된 경우 호출될 함수로 OnTargetDetect 설정
	MonsterPerception->OnTargetPerceptionUpdated.AddDynamic(this,
		&AGHNormalMonsterController::OnTargetDetect);
	// Target 을 놓칠 경우 호출될 함수로 OnTargetForget 설정
	MonsterPerception->OnTargetPerceptionForgotten.AddDynamic(this,
		&AGHNormalMonsterController::OnTargetForget);
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

void AGHNormalMonsterController::OnTargetDetect(AActor* Target, FAIStimulus Stimulus)
{
	// 감지에 성공한 경우
	if (Stimulus.WasSuccessfullySensed())
	{
		ETeamAttitude::Type Relationship = GetTeamAttitudeTowards(*Target);

		// 기존 Target 과 다른 객체이고 아군이 아닌경우 Target으로 인식
		if (Target != Blackboard->GetValueAsObject(TEXT("Target"))
			&& Relationship != ETeamAttitude::Friendly)
		{
			Blackboard->SetValueAsObject(TEXT("Target"), Target);
		}
	}
	else
	{
		// Target 감지 실패한 경우
		UObject* Target = Blackboard->GetValueAsObject(FName("Target"));
		if (nullptr != Target)
		{
			// 기존에 Target이 존재했다면 PreTarget으로 전환해준다.
			Blackboard->SetValueAsObject(FName("PreTarget"), Target);
		}

		Blackboard->SetValueAsObject(FName("Target"), nullptr);
	}
}

void AGHNormalMonsterController::OnTargetForget(AActor* Target)
{
	// 
}
