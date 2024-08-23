// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GHCharacterBase.h"

AGHCharacterBase::AGHCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

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

