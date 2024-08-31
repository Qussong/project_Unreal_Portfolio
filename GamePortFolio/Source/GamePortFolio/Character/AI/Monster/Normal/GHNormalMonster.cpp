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

AGHNormalMonster::AGHNormalMonster()
{
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

	// UI Section
	HUDWidgetComp = CreateDefaultSubobject<UGHMonsterWidgetComponent>(TEXT("HUDWidgetComp"));
	if (IsValid(HUDWidgetComp))
	{
		HUDWidgetComp->SetupAttachment(RootComponent);
		HUDWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
		HUDWidgetComp->SetVisibility(true);
		HUDWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
		HUDWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		static ConstructorHelpers::FClassFinder<UGHMonsterWidget>
			HUDWidgetRef(TEXT("/Game/Gihoon/UI/WB_MonsterHUD.WB_MonsterHUD_C"));
		if (HUDWidgetRef.Succeeded())
		{
			HUDWidgetComp->SetWidgetClass(HUDWidgetRef.Class);
		}
	}
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

void AGHNormalMonster::UpdateHUD()
{
	UUserWidget* Widget = HUDWidgetComp->GetWidget();
	if (IsValid(Widget))
	{
		UGHMonsterWidget* MonsterWidget = Cast<UGHMonsterWidget>(Widget);
		if (IsValid(MonsterWidget))
		{
			// Progress Bar
			UProgressBar* HpBar = Cast<UProgressBar>(MonsterWidget->GetWidgetFromName(TEXT("GHHealthBar")));
			if (IsValid(HpBar))
			{
				HpBar->SetPercent(Stat->GetCurrnetHealth() / Stat->GetMaxHealth());
			}

			// Text Block
			UTextBlock* CurHpTxtBlock = Cast<UTextBlock>(MonsterWidget->GetWidgetFromName(TEXT("GHCurrentHealth")));
			UTextBlock* MaxHpTxtBlock = Cast<UTextBlock>(MonsterWidget->GetWidgetFromName(TEXT("GHMaxHealth")));
			if (IsValid(CurHpTxtBlock) && IsValid(MaxHpTxtBlock))
			{
				float CurHp = Stat->GetCurrnetHealth();
				float MaxHp = Stat->GetMaxHealth();

				CurHpTxtBlock->SetText(FText::AsNumber(CurHp));
				MaxHpTxtBlock->SetText(FText::AsNumber(MaxHp));
			}
		}
	}
}

float AGHNormalMonster::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UpdateHUD();

	AGHNormalMonsterController* MonsterController = Cast<AGHNormalMonsterController>(GetController());
	MonsterController->GetBlackboardComponent()->SetValueAsBool(TEXT("IsHit"), true);
	MonsterController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), DamageCauser);

	return DamageAmount;
}
