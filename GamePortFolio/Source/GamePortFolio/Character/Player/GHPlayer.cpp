// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/GHPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/GHPlayerInputAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Controller/GHPlayerController.h"
#include "UI/Player/GHPlayerWidget.h"
#include "Components/ProgressBar.h"
#include "Stat/Player/GHPlayerStatComponent.h"
#include "Component/Inventory/GHInventoryComponent.h"
#include "Animation/Player/GHPlayerAnim.h"
#include "Item/Equip/GHWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ChildActorComponent.h"
#include "Camera/PlayerAttack/GHPlayerAttackCameraShake.h"
#include "Sound/SoundCue.h"
#include "Components/TextBlock.h"
#include "Particles/ParticleSystem.h"
#include "Components/Button.h"


AGHPlayer::AGHPlayer()
{
	// Tick Section
	PrimaryActorTick.bCanEverTick = true;

	// Team Section
	SetTeamID(ETeamID::PLAYER);

	// Camera Section
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetWorldRotation(FRotator(-50.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 1400.f;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->FieldOfView = 55.f;

	// Capsule Section
	GetCapsuleComponent()->InitCapsuleSize(30.f, 90.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerProfile"));

	// Skeletal Mesh Section
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		PlayerMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Gihoon/UE_Characters/Mannequin_UE4/Meshes/SK_Mannequin_GH.SK_Mannequin_GH'"));
	if (PlayerMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(PlayerMeshRef.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	
	// AnimInstance Section
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		PlayerAnimClassRef(TEXT("/Game/Gihoon/Animations/Player/ABP_GHPlayer.ABP_GHPlayer_C"));
	if (PlayerAnimClassRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnimClassRef.Class);
	}

	// IMC Section
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		IMCRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Gihoon/Input/IMC_Player.IMC_Player'"));
	if (IMCRef.Succeeded())
	{
		IMC = IMCRef.Object;
	}

	// Player State Widget Section
	static ConstructorHelpers::FClassFinder<UGHPlayerWidget>
		StateWidgetRef(TEXT("/Game/Gihoon/UI/WB_Player.WB_Player_C"));
	if (StateWidgetRef.Succeeded())
	{
		StateWidgetClass = StateWidgetRef.Class;
	}

	// GameOver Widget Section
	static ConstructorHelpers::FClassFinder<UGHPlayerWidget>
		GameOverWidgetRef(TEXT("/Game/Gihoon/UI/WB_GameOver.WB_GameOver_C"));
	if (GameOverWidgetRef.Succeeded())
	{
		GameOverWidgetClass = GameOverWidgetRef.Class;
	}

	// YouDie Widget Section
	static ConstructorHelpers::FClassFinder<UGHPlayerWidget>
		YouDieWidgetRef(TEXT("/Game/Gihoon/UI/WB_Youdie.WB_Youdie_C"));
	if (YouDieWidgetRef.Succeeded())
	{
		YouDieWidgetClass = YouDieWidgetRef.Class;
	}

	// Inventory Section
	Inventory = CreateDefaultSubobject<UGHInventoryComponent>(TEXT("Inventory"));

	// Stat Section
	Stat = CreateDefaultSubobject<UGHPlayerStatComponent>(TEXT("PlayerStat"));
	Stat->SetMaxHealth(200.f);
	Stat->SetATK(20.f);
	Stat->SetDEF(10.f);

	// Hit Section
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		HitParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Blood/P_Blood_Splat_Cone.P_Blood_Splat_Cone'"));
	if (HitParticleRef.Succeeded())
	{
		HitParticle = HitParticleRef.Object;
	}

}

void AGHPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AGHPlayer::BeginPlay()
{
	Super::BeginPlay();

	// IMC Section
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (IsValid(PlayerController))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (IsValid(Subsystem))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}

		AGHPlayerController* CustomController = Cast<AGHPlayerController>(PlayerController);
		if (IsValid(CustomController))
		{
			MyController = CustomController;
		}
	}

	// Player State Widget Section
	if (IsValid(StateWidgetClass))
	{
		StateWidgetInstance = CreateWidget<UGHPlayerWidget>(GetWorld(), StateWidgetClass);
		StateWidgetInstance->AddToViewport();
		UpdateStateWidget();
	}
	
	// GameOver Widget Section
	if (IsValid(GameOverWidgetClass))
	{
		GameOverWidgetInstance = CreateWidget<UGHPlayerWidget>(GetWorld(), GameOverWidgetClass);
		YesBtn = Cast<UButton>(GameOverWidgetInstance->GetWidgetFromName(TEXT("YesBtn")));
		NoBtn = Cast<UButton>(GameOverWidgetInstance->GetWidgetFromName(TEXT("NoBtn")));
		YesBtn->OnClicked.AddDynamic(this, &AGHPlayer::YesBtnClicked);
		NoBtn->OnClicked.AddDynamic(this, &AGHPlayer::NoBtnClicked);
	}

	// YouDie Widget Section
	if (IsValid(YouDieWidgetClass))
	{
		YouDieWidgetInstance = CreateWidget<UGHPlayerWidget>(GetWorld(), YouDieWidgetClass);
		MainBtn = Cast<UButton>(YouDieWidgetInstance->GetWidgetFromName(TEXT("MainBtn")));
		MainBtn->OnClicked.AddDynamic(this, &AGHPlayer::MainBtnClicked);
	}

	// Anim Section
	Anim = Cast<UGHPlayerAnim>(GetMesh()->GetAnimInstance());

}

void AGHPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyController->IsZoomIn())
	{
		MyController->ZoomIn(DeltaTime);
	}
}

void AGHPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	const UGHPlayerInputAction* PlayerInput = GetDefault<UGHPlayerInputAction>();
	if (IsValid(EnhancedInputComp) && IsValid(PlayerInput))
	{
		// Move
		MoveActionValue = &EnhancedInputComp->BindActionValue(PlayerInput->IA_SetDestination);
		EnhancedInputComp->BindAction(PlayerInput->IA_SetDestination, ETriggerEvent::Triggered, this, &AGHPlayer::IA_SetDestination_Triggered);
		EnhancedInputComp->BindAction(PlayerInput->IA_SetDestination, ETriggerEvent::Started, this, &AGHPlayer::IA_SetDestination_Started);
		EnhancedInputComp->BindAction(PlayerInput->IA_SetDestination, ETriggerEvent::Canceled, this, &AGHPlayer::IA_SetDestination_Canceled);
		EnhancedInputComp->BindAction(PlayerInput->IA_SetDestination, ETriggerEvent::Completed, this, &AGHPlayer::IA_SetDestination_Completed);
		// Item Slot
		EnhancedInputComp->BindAction(PlayerInput->IA_SlotNum1, ETriggerEvent::Started, this, &AGHPlayer::IA_SlotNum1_Started);
		// Drop
		DropActionValue = &EnhancedInputComp->BindActionValue(PlayerInput->IA_Drop);
		// Inventory
		EnhancedInputComp->BindAction(PlayerInput->IA_Inventory, ETriggerEvent::Started, this, &AGHPlayer::IA_Inventory_Started);
		// Equip
		EnhancedInputComp->BindAction(PlayerInput->IA_Equip, ETriggerEvent::Started, this, &AGHPlayer::IA_Equip_Started);
		// Noraml Attack
		EnhancedInputComp->BindAction(PlayerInput->IA_NormalAttack, ETriggerEvent::Started, this, &AGHPlayer::IA_NormalAttack_Started);
	}
}

void AGHPlayer::SetDeath()
{
	Super::SetDeath();

	// 플레이어 컨트롤러 타깃 변경
	AGHPlayerController* PlayerController = Cast<AGHPlayerController>(GetController());
	if (IsValid(PlayerController) && IsValid(GameOverWidgetInstance))
	{
		// GameOver Widget 출력
		GameOverWidgetInstance->AddToViewport();

		// 입력 타깃 변경 : Game -> GameOver Widget
		FInputModeUIOnly InputUIMode;
		InputUIMode.SetWidgetToFocus(GameOverWidgetInstance->TakeWidget());
		PlayerController->SetInputMode(InputUIMode);
	}

	// 플레이어 이동 중지
	GetCharacterMovement()->StopMovementImmediately();

	// 플레이어 충돌 정지
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Dead 애니메이션 재생
	Anim->PlayKnockDownMontage();
}

void AGHPlayer::UpdateStateWidget()
{
	UGHPlayerStatComponent* PlayerStat = Cast<UGHPlayerStatComponent>(Stat);
	if (IsValid(StateWidgetInstance) && IsValid(PlayerStat))
	{
		StateWidgetInstance->GetHealthBar()->SetPercent(PlayerStat->GetCurrnetHealth() / PlayerStat->GetMaxHealth());
		StateWidgetInstance->GetManaBar()->SetPercent(PlayerStat->GetCurrentMana() / PlayerStat->GetMaxMana());
		StateWidgetInstance->GetStaminaBar()->SetPercent(PlayerStat->GetCurrentStamina() / PlayerStat->GetMaxStamina());
		StateWidgetInstance->GetEXPBar()->SetPercent(PlayerStat->GetCurrentEXP() / PlayerStat->GetMaxEXP());

		float CurHp = Stat->GetCurrnetHealth();
		float MaxHp = Stat->GetMaxHealth();
		float CurMana = PlayerStat->GetCurrentMana();
		float MaxMana = PlayerStat->GetMaxMana();
		StateWidgetInstance->GetCurHealthTextBlock()->SetText(FText::AsNumber(CurHp));
		StateWidgetInstance->GetMaxHealthTextBlock()->SetText(FText::AsNumber(MaxHp));
		StateWidgetInstance->GetCurManaTextBlock()->SetText(FText::AsNumber(CurMana));
		StateWidgetInstance->GetMaxManaTextBlock()->SetText(FText::AsNumber(MaxMana));
	}
}

void AGHPlayer::YesBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Click Yes Btn"));

	// 현재 레벨로 이동
	UGameplayStatics::OpenLevel(this, FName("CurrentLevel"));

	// 입력 타깃 변경 : GameOver Widget -> Game
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (PlayerController)
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(false);
		PlayerController->SetInputMode(InputMode);
	}
}

void AGHPlayer::NoBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Click No Btn"));

	// 플레이어 컨트롤러 타깃 변경
	AGHPlayerController* PlayerController = Cast<AGHPlayerController>(GetController());
	if (IsValid(PlayerController) && IsValid(YouDieWidgetInstance))
	{
		// Platyer State Widget 제거
		StateWidgetInstance->RemoveFromParent();

		// GameOver Widget 제거
		GameOverWidgetInstance->RemoveFromParent();

		// YouDie Widget 출력
		YouDieWidgetInstance->AddToViewport();

		// 입력 타깃 변경 : GameOver Widget -> YouDie Widget
		FInputModeUIOnly InputUIMode;
		InputUIMode.SetWidgetToFocus(YouDieWidgetInstance->TakeWidget());
		PlayerController->SetInputMode(InputUIMode);
	}

	// Player 클로즈업
	MyController->SetZoomIn(true);
	// Dead 애니메이션 재생
	Anim->PlayDeathMontage();

}

void AGHPlayer::MainBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Click Main Btn"));
}

UChildActorComponent* AGHPlayer::FindChildActorMap(FName Name)
{
	UChildActorComponent** Result = ChildActorMap.Find(Name);

	if (Result != nullptr)
		return *Result;
	else
		return nullptr;
}

void AGHPlayer::AddChildActorMap(FName Name, UChildActorComponent* ChildActor)
{
	ChildActorMap.Add(Name, ChildActor);
}

void AGHPlayer::IA_SetDestination_Triggered(const FInputActionValue& Value)
{
	Cast<AGHPlayerController>(GetController())->GetLocationUnderCursor();
	Cast<AGHPlayerController>(GetController())->Follow();
}

void AGHPlayer::IA_SetDestination_Started(const FInputActionValue& Value)
{
	GetCharacterMovement()->StopMovementImmediately();
}

void AGHPlayer::IA_SetDestination_Canceled(const FInputActionInstance& Value)
{
}

void AGHPlayer::IA_SetDestination_Completed(const FInputActionInstance& Value)
{
	float ElapsedTime = Value.GetElapsedTime();

	if (ElapsedTime < 0.5f)
	{
		Cast<AGHPlayerController>(GetController())->MoveTo();
	}
}

void AGHPlayer::IA_SlotNum1_Started(const FInputActionValue& Value)
{
	if (IsValid(Stat))
	{
		float Damage = 100.f;
		UGameplayStatics::ApplyDamage(this, Damage, GetController(), this, UDamageType::StaticClass());
	}

	UE_LOG(LogTemp, Log, TEXT("Slot Num1"));
}

void AGHPlayer::IA_Inventory_Started(const FInputActionValue& Value)
{
	Inventory->ReviewInventory();
}

void AGHPlayer::IA_Equip_Started(const FInputActionValue& Value)
{
	if (ChildActorMap.IsEmpty()) return;

	if (false == isEquip)
	{
		Inventory->Armed(FName("Sword"));
		isEquip = true;
		isCombat = true;
	}
	else
	{
		Inventory->DisArmed(FName("Sword"));
		isEquip = false;
		isCombat = false;
	}
}

void AGHPlayer::IA_NormalAttack_Started(const FInputActionValue& Value)
{
	// 장비 장착여부 확인
	if (isEquip)
	{
		isCombat = true;

		// 피격대상 컨테이너 비워줌
		HitCheckContainer.Empty();

		// 플레이어 이동 중지
		GetCharacterMovement()->StopMovementImmediately();

		// 공격 애니메이션 재생
		Anim->PlayNormalAttackMontage();

		UE_LOG(LogTemp, Log, TEXT("Player Attack"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No Weapon"));
	}
}

void AGHPlayer::AttackCheck_Begin(FVector& Start_V, FVector End_V, FVector& Start_H, FVector& End_H)
{
	if (this == nullptr) return;

	UChildActorComponent** SwordActorComp = ChildActorMap.Find(FName("Sword"));
	if (nullptr != SwordActorComp)
	{
		AActor* ChildActor = (*SwordActorComp)->GetChildActor();
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
	}
}

void AGHPlayer::AttackCheck_Tick(FVector& Start_V, FVector End_V, FVector& Start_H, FVector& End_H)
{
	if (this == nullptr) return;

	if (isEquip)
	{
		UChildActorComponent** SwordActorComp = ChildActorMap.Find(FName("Sword"));
		if (nullptr != SwordActorComp)
		{
			AActor* ChildActor = (*SwordActorComp)->GetChildActor();
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
			bool IsHit = GetWorld()->LineTraceMultiByChannel(HitResultsVertical, Start_V, End_V, ECC_GameTraceChannel4, CollisionParamsVertical);

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
			IsHit = GetWorld()->LineTraceMultiByChannel(HitResultsHorizontal, Start_H, End_H, ECC_GameTraceChannel4, CollisionParamsVertical);

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
}

void AGHPlayer::EnemyHit(TArray<FHitResult>& HitResults)
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

	// 카메라 처리
	TSubclassOf<UCameraShakeBase> ShakeClass = UGHPlayerAttackCameraShake::StaticClass();	// 카메라 셰이크 클래스
	FVector Epicenter = GetActorLocation();	// 카메라 셰이크 발생 위치
	float InnerRadius = 10.0f;	// 셰이크 강도가 최대치로 적용될 반경 설정
	float OuterRadius = 2000.0f;	// 셰이크 강도가 사라지는 외곽 반경 설정
	float Falloff = 1.0f;	// 셰이크 강도 감소 비율 설정
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), ShakeClass, Epicenter, InnerRadius, OuterRadius, Falloff);
}

float AGHPlayer::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// UI 업데이트
	UpdateStateWidget();

	if (Stat->GetCurrnetHealth() <= 0.f)
	{
		SetDeath();
	}

	return 0.0f;
}
