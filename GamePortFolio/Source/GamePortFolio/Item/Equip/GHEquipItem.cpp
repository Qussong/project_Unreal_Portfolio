// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Equip/GHEquipItem.h"
#include "Components/BoxComponent.h"

AGHEquipItem::AGHEquipItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// Collision Section
	ItemCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	ItemCollisionComp->SetupAttachment(RootComponent);
	ItemCollisionComp->SetCollisionProfileName(TEXT("ItemProfile"));
	ItemCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGHEquipItem::OnOverlapBegin);
	ItemCollisionComp->OnComponentEndOverlap.AddDynamic(this, &AGHEquipItem::OnEndOverlap);
}

void AGHEquipItem::BeginPlay()
{
	Super::BeginPlay();
}

void AGHEquipItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGHEquipItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AGHEquipItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
