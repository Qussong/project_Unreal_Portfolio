// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Monster/GHMonster.h"
#include "Animation/AI/Monster/GHMonsterAnim.h"
#include "Controller/AI/GHAIController.h"
#include "Components/CapsuleComponent.h"
#include "UI/Monster/GHMonsterWidgetComponent.h"
#include "UI/Monster/GHMonsterWidget.h"
#include "Components/TextBlock.h"
#include "Stat/GHBaseStatComponent.h"
#include "Components/ProgressBar.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"

AGHMonster::AGHMonster()
{
	// Team Section
	SetTeamID(ETeamID::MONSTER);

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

	// Hit Section
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		HitParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Blood/P_Blood_Splat_Cone.P_Blood_Splat_Cone'"));
	if (HitParticleRef.Succeeded())
	{
		HitParticle = HitParticleRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue>
		HitSoundRef(TEXT("/Script/Engine.SoundCue'/Game/Gihoon/Sound/HitSound_Cue.HitSound_Cue'"));
	if (HitSoundRef.Succeeded())
	{
		HitSoundCue = HitSoundRef.Object;
	}
}

void AGHMonster::SetDeath()
{
	Super::SetDeath();

	//UE_LOG(LogTemp, Log, TEXT("Monster Death"));

	SetState(EMonsterState::DEATH);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AGHAIController* MonsterController = Cast<AGHAIController>(GetController());
	if (IsValid(MonsterController))
	{
		MonsterController->StopAI();
	}
}

void AGHMonster::SetState(EMonsterState NewState)
{
	MonsterPrevState = MonsterState;
	MonsterState = NewState;

	if (nullptr == MonsterAnim) return;

	switch (MonsterState)
	{
	case EMonsterState::IDLE:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::IDLE);
		break;
	case EMonsterState::TRACE:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::RUN);
		break;
	case EMonsterState::ATTACK:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::ATTACK);
		break;
	case EMonsterState::DEATH:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::DEATH);
		break;
	case EMonsterState::ANGRY:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::ANGRY);
		break;
	case EMonsterState::HIT:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::HIT);
		break;
	// Normal
	case EMonsterState::DETECT:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::DETECT);
		break;
	// Epic
	case EMonsterState::WAIT:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::WAIT);
		break;
	case EMonsterState::READYFIGHT:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::READYFIGHT);
		break;
	case EMonsterState::BACKSTEP:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::BACKSTEP);
		break;
	case EMonsterState::BOUNDARY:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::BOUNDARY);
		break;
	case EMonsterState::ATTACK2:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::ATTACK2);
		break;
	case EMonsterState::ATTACK3:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::ATTACK3);
		break;
	default:
		//
		break;
	}
}

void AGHMonster::UpdateHUD()
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