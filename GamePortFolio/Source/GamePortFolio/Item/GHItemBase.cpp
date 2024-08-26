// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GHItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

AGHItemBase::AGHItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// DataTable Section
	static ConstructorHelpers::FObjectFinder<UDataTable> 
		ItemDataTableRef(TEXT("/Script/Engine.DataTable'/Game/Gihoon/Item/Data/DT_Inventory.DT_Inventory'"));
	if (ItemDataTableRef.Succeeded())
	{
		ItemDataTable = ItemDataTableRef.Object;
	}

	// Collision Section
	ItemCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("ItemCollision"));
	RootComponent = ItemCollisionComp;
	ItemCollisionComp->SetSphereRadius(100.f);
	ItemCollisionComp->SetCollisionProfileName(TEXT("ItemProfile"));

	// StaticMesh Section
	ItemStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMeshComp->SetupAttachment(RootComponent);

	// SkeletalMesh Section
	ItemSkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMesh"));
	ItemSkeletalMeshComp->SetupAttachment(RootComponent);
}

void AGHItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGHItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGHItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

