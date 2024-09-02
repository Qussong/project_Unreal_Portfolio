// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Monster/Normal/GHNormalMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Controller/AI/Monster/Normal/GHNormalMonsterController.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AI/Monster/GHMonsterAnim.h"
#include "UI/Monster/GHMonsterWidgetComponent.h"
#include "UI/Monster/GHMonsterWidget.h"
#include "Components/TextBlock.h"
#include "Stat/GHBaseStatComponent.h"
#include "Components/ProgressBar.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


AGHNormalMonster::AGHNormalMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	// Controller Section
	AIControllerClass = AGHNormalMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Movement Section
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

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

	// Stat Section
	Stat->SetMaxHealth(100.f);
	Stat->SetATK(20.f);
	Stat->SetDEF(10.f);
}		

void AGHNormalMonster::BeginPlay()
{
	Super::BeginPlay();

	// Animation Section
	MonsterAnim = Cast<UGHMonsterAnim>(GetMesh()->GetAnimInstance());

	// UI Section
	UpdateHUD();
}

void AGHNormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGHNormalMonster::SetDeath()
{
	Super::SetDeath();

	HUDWidgetComp->SetVisibility(false);
}

float AGHNormalMonster::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UpdateHUD();

	AGHNormalMonsterController* MonsterController = Cast<AGHNormalMonsterController>(GetController());
	MonsterController->GetBlackboardComponent()->SetValueAsBool(TEXT("IsHit"), true);
	bool IsMonster = DamageCauser->IsA(AGHMonster::StaticClass());
	if (false == IsMonster)
	{
		MonsterController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), DamageCauser);
	}

	return DamageAmount;
}

void AGHNormalMonster::AttackCheck_Begin()
{
	HitCheckContainer.Empty();
	Center = GetMesh()->GetSocketLocation(FName("RightHandSocket"));
}

void AGHNormalMonster::AttackCheck_Tick()
{
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	bool IsHit = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		Center,
		Radius,
		TArray<TEnumAsByte<EObjectTypeQuery>>(), // 체크할 오브젝트 타입들
		nullptr,			// 필터할 클래스, nullptr이면 모든 클래스 포함
		IgnoreActors,		// 무시할 액터들
		OverlappedActors	// 결과로 반환될 액터들
	);

	if (IsHit)
	{
		Hit(OverlappedActors);
#if ENABLE_DRAW_DEBUG
		DrawDebugSphere(
			GetWorld(),		// 월드 컨텍스트
			Center,			// 구의 중심
			Radius,         // 구의 반지름
			3,              // 구의 세그먼트 수 (더 높은 값은 더 원에 가까운 구를 만듭니다)
			FColor::Red,	// 구의 색상
			false,          // 지속 시간 동안 표시될 것인지 여부 (true = 지속, false = 잠시)
			1.0f            // 지속 시간 (0이면 한 프레임 동안만 표시)
		);
#endif
	}
	else
	{
#if ENABLE_DRAW_DEBUG
		DrawDebugSphere(GetWorld(), Center,Radius, 3, FColor::Green, false, 1.0f);
#endif
	}

	Center = GetMesh()->GetSocketLocation(FName("RightHandSocket"));
}

void AGHNormalMonster::Hit(TArray<AActor*>& HitResults)
{
	// 오버랩된 액터들에 대해 처리
	for (AActor* Hitter : HitResults)
	{
		bool IsContain = HitCheckContainer.Contains(Hitter);
		if (false == IsContain)
		{
			HitCheckContainer.Add(Hitter);
			
			// 데미지 처리
			HitCheckContainer.Add(Hitter);
			UGameplayStatics::ApplyDamage(Hitter, Stat->GetATK(), GetController(), this, UDamageType::StaticClass());

			// 파티클 처리
			UParticleSystem* HitEffect = Cast<AGHCharacterBase>(Hitter)->GetHitParticle();
			if (nullptr != HitEffect)
			{
				FVector HitLocation = Hitter->GetActorLocation();
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitLocation);
			}

			// 사운드 처리
		}
	}
}
