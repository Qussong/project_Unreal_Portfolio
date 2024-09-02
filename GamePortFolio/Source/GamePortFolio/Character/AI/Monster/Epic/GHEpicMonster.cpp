
#include "Character/AI/Monster/Epic/GHEpicMonster.h"
#include "Controller/AI/Monster/Epic/GHEpicMonsterController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Stat/GHBaseStatComponent.h"

AGHEpicMonster::AGHEpicMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	// Controller Section
	AIControllerClass = AGHEpicMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Movement Section
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	// Skeletal Mesh Section
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		EpicMonsterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Mixamo/Mesh/YBot/Y_Bot.Y_Bot'"));
	if (EpicMonsterMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(EpicMonsterMeshRef.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// AnimInstance Section
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		EpicMonsterAnimRef(TEXT("/Game/Gihoon/Animations/Monster/Epic/ABP_EpicMonster.ABP_EpicMonster_C"));
	if (EpicMonsterAnimRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(EpicMonsterAnimRef.Class);
	}

	// Collision Section
	GetCapsuleComponent()->InitCapsuleSize(30.f, 90.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterProfile"));

	// Stat Section
	Stat->SetMaxHealth(500.f);
	Stat->SetATK(30.f);
	Stat->SetDEF(20.f);

}

void AGHEpicMonster::BeginPlay()
{
	Super::BeginPlay();

}

void AGHEpicMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
