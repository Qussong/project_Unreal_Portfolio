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
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->JumpZVelocity = 420.f;
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

