// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BaseActorComponent.h"

UBaseActorComponent::UBaseActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBaseActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UBaseActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

