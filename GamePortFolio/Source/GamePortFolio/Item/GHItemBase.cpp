// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GHItemBase.h"

AGHItemBase::AGHItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGHItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGHItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

