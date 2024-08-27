// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GHItemBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UI/Item/GHItemWidgetComponent.h"
#include "UI/GHBaseWidget.h"
#include "Components/SphereComponent.h"

AGHItemBase::AGHItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// DataTable Section
	static ConstructorHelpers::FObjectFinder<UDataTable> 
		ItemDataTableRef(TEXT("/Script/Engine.DataTable'/Game/Gihoon/Item/Data/DT_InventoryItem.DT_InventoryItem'"));
	if (ItemDataTableRef.Succeeded())
	{
		ItemDataTable = ItemDataTableRef.Object;
	}

	// Scene Section
	ItemSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("ItemScene"));
	RootComponent = ItemSceneComp;
	ItemSceneComp->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	ItemSceneComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	// SkeletalMesh Section
	ItemSkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMesh"));
	ItemSkeletalMeshComp->SetupAttachment(RootComponent);

	// StaticMesh Section
	ItemStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMeshComp->SetupAttachment(RootComponent);

	// Movement Section
	RotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovementComp->RotationRate = FRotator(0.f, 45.f, 0.f);

	// Collision Section
	ItemCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	ItemCollisionComp->SetupAttachment(RootComponent);
	ItemCollisionComp->SetSphereRadius(100.f);
	ItemCollisionComp->SetCollisionProfileName(TEXT("ItemProfile"));

	// ID Section
	OnIDChanged.AddDynamic(this, &AGHItemBase::HandleIDChanged);
	ID = FName("Cube");
	HandleIDChanged(ID);

	// UI Section
	PickupWidget = CreateDefaultSubobject<UGHItemWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);
	PickupWidget->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	static ConstructorHelpers::FClassFinder<UGHBaseWidget>
		PickupBoardRef(TEXT("/Game/Gihoon/UI/WB_Pickup.WB_Pickup_C"));
	if (PickupBoardRef.Succeeded())
	{
		PickupWidget->SetWidgetClass(PickupBoardRef.Class);
		PickupWidget->SetWidgetSpace(EWidgetSpace::Screen);
		PickupWidget->SetDrawAtDesiredSize(true);
		PickupWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
		
}

void AGHItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AGHItemBase::BeginPlay()
{
	Super::BeginPlay();

}

void AGHItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGHItemBase::SetID(FName NewID)
{
	if (ID != NewID)
	{
		ID = NewID;
		OnIDChanged.Broadcast(ID);
	}
}

void AGHItemBase::HandleIDChanged(FName NewID)
{
	FItemInventoryData* ItemData = ItemDataTable->FindRow<FItemInventoryData>(NewID, TEXT(""));
	if (nullptr == ItemData) return;

	// Skeletal Mesh Section
	USkeletalMesh* ItemSkeletalMesh = (ItemData->PickupSkeletalMesh).LoadSynchronous();
	if (IsValid(ItemSkeletalMesh))
	{
		ItemSkeletalMeshComp->SetSkeletalMesh(ItemSkeletalMesh);
	}
		
	// Static Mesh Section
	UStaticMesh* ItemStaticMesh = (ItemData->PickupStaticMesh).LoadSynchronous();
	if (IsValid(ItemStaticMesh))
	{
		ItemStaticMeshComp->SetStaticMesh(ItemStaticMesh);
	}
}

//void AGHItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//
//}

