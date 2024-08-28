// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GHBaseItem.h"

AGHBaseItem::AGHBaseItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// Scene Section
	ItemSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("ItemScene"));
	RootComponent = ItemSceneComp;
	ItemSceneComp->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	// SkeletalMesh Section
	ItemSkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMesh"));
	ItemSkeletalMeshComp->SetupAttachment(RootComponent);
	ItemSkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// StaticMesh Section
	ItemStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMeshComp->SetupAttachment(RootComponent);
	ItemStaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGHBaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGHBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

