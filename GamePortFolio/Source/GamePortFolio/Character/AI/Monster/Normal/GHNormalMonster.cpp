// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Monster/Normal/GHNormalMonster.h"
#include "Controller/AI/Monster/Normal/GHNormalMonsterController.h"
#include "Components/CapsuleComponent.h"

AGHNormalMonster::AGHNormalMonster()
{
	// Controller Section
	AIControllerClass = AGHNormalMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Skeletal Mesh Section
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		NormalMonsterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Mixamo/Mesh/XBot/X_Bot.X_Bot'"));
	if (NormalMonsterMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(NormalMonsterMeshRef.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// AnimInstance Section
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		NormalMonsterAnimRef(TEXT("/Game/Gihoon/Animations/Monster/Normal/ABP_NormalMonster.ABP_NormalMonster_C"));
	if (NormalMonsterAnimRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(NormalMonsterAnimRef.Class);
	}

	// Collision Section
	GetCapsuleComponent()->InitCapsuleSize(30.f, 90.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterProfile"));
}		

void AGHNormalMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AGHNormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}