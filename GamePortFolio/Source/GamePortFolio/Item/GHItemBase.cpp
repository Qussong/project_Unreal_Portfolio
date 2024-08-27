// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GHItemBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UI/Item/GHItemWidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Character/Player/GHPlayer.h"
#include "UI/Item/GHPickupWidget.h"
#include "Components/TextBlock.h"

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

	// SkeletalMesh Section
	ItemSkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMesh"));
	ItemSkeletalMeshComp->SetupAttachment(RootComponent);
	ItemSkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// StaticMesh Section
	ItemStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMeshComp->SetupAttachment(RootComponent);
	ItemStaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Movement Section
	RotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovementComp->RotationRate = FRotator(0.f, 45.f, 0.f);

	// Collision Section
	ItemCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	ItemCollisionComp->SetupAttachment(RootComponent);
	ItemCollisionComp->SetSphereRadius(150.f);
	ItemCollisionComp->SetCollisionProfileName(TEXT("ItemProfile"));
	ItemCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGHItemBase::OnOverlapBegin);
	ItemCollisionComp->OnComponentEndOverlap.AddDynamic(this, &AGHItemBase::OnEndOverlap);

	// UI Section
	PickupWidgetComp = CreateDefaultSubobject<UGHItemWidgetComponent>(TEXT("PickupWidget"));
	if(IsValid(PickupWidgetComp))
	{
		PickupWidgetComp->SetupAttachment(RootComponent);
		PickupWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
		PickupWidgetComp->SetVisibility(false);
		PickupWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
		PickupWidgetComp->SetDrawAtDesiredSize(true);
		PickupWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		static ConstructorHelpers::FClassFinder<UGHPickupWidget>
			PickupBoardRef(TEXT("/Game/Gihoon/UI/WB_Pickup.WB_Pickup_C"));
		if (PickupBoardRef.Succeeded())
		{
			PickupWidgetComp->SetWidgetClass(PickupBoardRef.Class);
		}
	}
		
	// ID Section
	//ID = FName("Cube");
	ID = FName("Sword");
	OnIDChanged.AddDynamic(this, &AGHItemBase::HandleIDChanged);
}

void AGHItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGHItemBase::BeginPlay()
{
	Super::BeginPlay();

	HandleIDChanged(ID);
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
	ItemData = ItemDataTable->FindRow<FItemInventoryData>(NewID, TEXT(""));
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

	// UI Section
	UUserWidget* Widget = PickupWidgetComp->GetWidget();
	if (IsValid(Widget))
	{
		UGHPickupWidget* PickupWidget = Cast<UGHPickupWidget>(Widget);
		if (IsValid(PickupWidget))
		{
			UTextBlock* TextBlock = Cast<UTextBlock>(PickupWidget->GetWidgetFromName(TEXT("ItemName")));
			if (IsValid(TextBlock))
			{
				TextBlock->SetText(ItemData->DisplayName);
			}
		}
	}

	// Custom Section
	if (FText::FromName(FName("Sword Item")).EqualTo(ItemData->DisplayName))
	{
		ItemStaticMeshComp->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
		ItemStaticMeshComp->SetRelativeLocation(FVector(0.f, 60.f, 70.f));
		ItemStaticMeshComp->SetRelativeRotation(FRotator(0.f, 0.f, 50.f));
	}
	if (FText::FromName(FName("Cube Item")).EqualTo(ItemData->DisplayName))
	{
		ItemStaticMeshComp->SetRelativeScale3D(FVector(.5f, .5f, .5f));
	}
}

void AGHItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	AGHPlayer* Player = Cast<AGHPlayer>(Character);
	if (IsValid(Player))
	{
		PickupWidgetComp->SetVisibility(true);
	}

	UE_LOG(LogTemp, Log, TEXT("Item Begin Overlap"));
}

void AGHItemBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	AGHPlayer* Player = Cast<AGHPlayer>(Character);
	if (IsValid(Player))
	{
		PickupWidgetComp->SetVisibility(false);
	}

	UE_LOG(LogTemp, Log, TEXT("Item End Overlap"));
}
