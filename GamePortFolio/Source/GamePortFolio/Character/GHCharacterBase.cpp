// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GHCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/GHBaseAnim.h"
#include "Stat/GHBaseStatComponent.h"

AGHCharacterBase::AGHCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Team Section
	SetGenericTeamId(ETeamID::NOTEAM);

	// Pawn Section
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// SkeletalMesh Section
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// Movement Section
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	// Stat Section
	Stat = CreateDefaultSubobject<UGHBaseStatComponent>(TEXT("Stat"));
}

void AGHCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AGHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGHCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGHCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AGHCharacterBase::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->DecreaseHealth(DamageAmount);
	return DamageAmount;
}

