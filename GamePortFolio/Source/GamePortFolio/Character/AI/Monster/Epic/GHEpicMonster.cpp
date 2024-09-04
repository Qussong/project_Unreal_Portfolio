
#include "Character/AI/Monster/Epic/GHEpicMonster.h"
#include "Controller/AI/Monster/Epic/GHEpicMonsterController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Stat/GHBaseStatComponent.h"
#include "Animation/AI/Monster/GHMonsterAnim.h"

#include "UI/Monster/GHMonsterWidgetComponent.h"
#include "UI/Monster/GHMonsterWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ChildActorComponent.h"
#include "Item/Equip/GHWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AGHEpicMonster::AGHEpicMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	// Controller Section
	AIControllerClass = AGHEpicMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Skeletal Mesh Section
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		EpicMonsterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Gihoon/UE_Characters/Mannequins/Meshes/SKM_Manny5_GH.SKM_Manny5_GH'"));
	if (EpicMonsterMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(EpicMonsterMeshRef.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// AnimInstance Section
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		EpicMonsterAnimRef(TEXT("/Game/Gihoon/Animations/Monster/Epic/ABP_EpicMonster_New.ABP_EpicMonster_New_C"));
	if (EpicMonsterAnimRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(EpicMonsterAnimRef.Class);
	}

	// Collision Section
	GetCapsuleComponent()->InitCapsuleSize(30.f, 90.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterProfile"));

	// Movement Section
	GetCharacterMovement()->MaxWalkSpeed = 450.f;

	// Weapon Section
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SwordObjectRef(TEXT("/Script/Engine.StaticMesh'/Game/Gihoon/Item/Mesh/SM_GHSword.SM_GHSword'"));
	if (SwordObjectRef.Succeeded())
	{
		SwordMesh = SwordObjectRef.Object;
	}

	WeaponActorComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponActorComp"));
	if (IsValid(WeaponActorComp))
	{
		// 부모 컴포넌트(SkeletalMesh)에 부착
		WeaponActorComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("clavicle_r_weaponhold"));
		// Child Actor Class 설정
		WeaponActorComp->SetChildActorClass(AGHWeapon::StaticClass());
		// 초기 트랜스폼 설정
		WeaponActorComp->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		WeaponActorComp->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	// Stat Section
	Stat->SetMaxHealth(500.f);
	Stat->SetATK(30.f);
	Stat->SetDEF(20.f);
}

void AGHEpicMonster::BeginPlay()
{
	Super::BeginPlay();

	SetState(EMonsterState::WAIT);

	// Animation Section
	MonsterAnim = Cast<UGHMonsterAnim>(GetMesh()->GetAnimInstance());

	// UI Section
	UpdateHUD();

	// Weapon Section
	if (IsValid(WeaponActorComp))
	{
		WeaponActorComp->RegisterComponent();	// 생성된 Child Actor Component 를 월드에 등록
		UStaticMeshComponent* WeaponStatiMeshComp = Cast<AGHWeapon>(WeaponActorComp->GetChildActor())->GetItemStaticMeshComp();
		if (IsValid(WeaponStatiMeshComp))
		{
			WeaponStatiMeshComp->SetStaticMesh(SwordMesh);
		}
	}
}

void AGHEpicMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGHEpicMonster::SetDeath()
{
	Super::SetDeath();

	HUDWidgetComp->SetVisibility(false);
}

float AGHEpicMonster::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UpdateHUD();

	AGHEpicMonsterController* MonsterController = Cast<AGHEpicMonsterController>(GetController());

	// Hit Section
	if (MonsterState == EMonsterState::BOUNDARY)
	{
		MonsterController->GetBlackboardComponent()->SetValueAsBool(TEXT("IsHit"), true);
	}

	// Target Setiing
	AActor* Target = Cast<AActor>(MonsterController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	bool IsMonster = DamageCauser->IsA(AGHMonster::StaticClass());
	if (nullptr == Target && false == IsMonster)
	{
		MonsterController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), DamageCauser);
	}

	return DamageAmount;
}

void AGHEpicMonster::AttackCheck_Begin(FVector& Start_V, FVector End_V, FVector& Start_H, FVector& End_H)
{
	if (this == nullptr) return;

	if (nullptr != WeaponActorComp)
	{
		AActor* ChildActor = WeaponActorComp->GetChildActor();
		if (nullptr == ChildActor) return;

		AGHWeapon* Weapon = Cast<AGHWeapon>(ChildActor);
		if (nullptr == Weapon) return;

		UStaticMeshComponent* SwordStaticMesh = Weapon->GetItemStaticMeshComp();
		if (nullptr == SwordStaticMesh) return;

		// Start_V, End_V 위치 설정
		Start_V = SwordStaticMesh->GetSocketLocation(FName("Start"));
		End_V = SwordStaticMesh->GetSocketLocation(FName("End"));
		// Start_H, End_H 위치 설정
		Start_H = End_V;
		End_H = End_V;

		// 피격대상 컨테이너 비워줌
		HitCheckContainer.Empty();
	}

}

void AGHEpicMonster::AttackCheck_Tick(FVector& Start_V, FVector End_V, FVector& Start_H, FVector& End_H)
{
	if (this == nullptr) return;

	if (nullptr != WeaponActorComp)
	{
		AActor* ChildActor = WeaponActorComp->GetChildActor();
		if (nullptr == ChildActor) return;

		AGHWeapon* Weapon = Cast<AGHWeapon>(ChildActor);
		if (nullptr == Weapon) return;

		UStaticMeshComponent* SwordStaticMesh = Weapon->GetItemStaticMeshComp();
		if (nullptr == SwordStaticMesh) return;

		// Start_V, End_V 위치 설정
		Start_V = SwordStaticMesh->GetSocketLocation(FName("Start"));
		End_V = SwordStaticMesh->GetSocketLocation(FName("End"));

		// End_H 위치 설정
		End_H = End_V;

		// Line1
		TArray<FHitResult> HitResultsVertical;
		FCollisionQueryParams CollisionParamsVertical;
		CollisionParamsVertical.AddIgnoredActor(this); // 자기 자신은 무시
		bool IsHit = GetWorld()->LineTraceMultiByChannel(HitResultsVertical, Start_V, End_V, ECC_GameTraceChannel5, CollisionParamsVertical);

		if (IsHit)
		{
			DrawDebugLine(GetWorld(), Start_V, End_V, FColor::Red, false, 1, 0, 1);
			EnemyHit(HitResultsVertical);
		}
		else
		{
			DrawDebugLine(GetWorld(), Start_V, End_V, FColor::Green, false, 1, 0, 1);
		}

		// Line2
		TArray<FHitResult> HitResultsHorizontal;
		FCollisionQueryParams CollisionParamsHorizontal;
		CollisionParamsVertical.AddIgnoredActor(this); // 자기 자신은 무시
		IsHit = GetWorld()->LineTraceMultiByChannel(HitResultsHorizontal, Start_H, End_H, ECC_GameTraceChannel5, CollisionParamsVertical);

		if (IsHit)
		{
			EnemyHit(HitResultsHorizontal);
#if ENABLE_DRAW_DEBUG
			DrawDebugLine(GetWorld(), Start_H, End_H, FColor::Red, false, 1, 0, 1);
#endif
		}
		else
		{
#if ENABLE_DRAW_DEBUG
			DrawDebugLine(GetWorld(), Start_H, End_H, FColor::Green, false, 1, 0, 1);
#endif
		}

		// Start_H 위치 설정
		Start_H = End_V;
	}
}

void AGHEpicMonster::EnemyHit(TArray<FHitResult>& HitResults)
{
	for (FHitResult HitResult : HitResults)
	{
		AActor* Hitter = HitResult.GetActor();
		bool isExist = HitCheckContainer.Contains(Hitter);
		if (false == isExist)
		{
			UE_LOG(LogTemp, Log, TEXT("HIT!!"));

			// 데미지 처리
			HitCheckContainer.Add(Hitter);
			UGameplayStatics::ApplyDamage(Hitter, Stat->GetATK(), GetController(), this, UDamageType::StaticClass());

			// 이펙트 처리
			UParticleSystem* HitEffect = Cast<AGHCharacterBase>(Hitter)->GetHitParticle();
			if (nullptr != HitEffect)
			{
				FVector HitLocation = HitResult.ImpactPoint;
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitLocation);
			}

			// 사운드 처리
			USoundCue* HitSound = Cast<AGHCharacterBase>(Hitter)->GetHitSound();
			if (nullptr != HitSound)
			{
				FVector HitLocation = HitResult.ImpactPoint;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, HitLocation);
			}
		}
	}
}

void AGHEpicMonster::AttackCheck_Begin2()
{
	HitCheckContainer.Empty();
	Attack2Center = GetMesh()->GetSocketLocation(FName("hand_l_weapon"));
}

void AGHEpicMonster::AttackCheck_Tick2()
{
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	bool IsHit = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		Attack2Center,
		Attack2Radius,
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
			Attack2Center,	// 구의 중심
			Attack2Radius,  // 구의 반지름
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
		DrawDebugSphere(GetWorld(), Attack2Center, Attack2Radius, 3, FColor::Green, false, 1.0f);
#endif
	}

	Attack2Center = GetMesh()->GetSocketLocation(FName("hand_l_weapon"));
}

void AGHEpicMonster::Hit(TArray<AActor*>& HitResults)
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
		}
	}
}
