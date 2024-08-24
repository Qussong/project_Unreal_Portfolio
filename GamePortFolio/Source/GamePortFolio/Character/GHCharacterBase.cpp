// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GHCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/GHBaseAnim.h"

AGHCharacterBase::AGHCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

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
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
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

