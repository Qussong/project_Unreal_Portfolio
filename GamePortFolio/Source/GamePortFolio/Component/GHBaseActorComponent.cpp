// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/GHBaseActorComponent.h"

UGHBaseActorComponent::UGHBaseActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGHBaseActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UGHBaseActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

