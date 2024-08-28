// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Pickup/GHPickupItem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "UI/Item/GHItemWidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Character/Player/GHPlayer.h"
#include "UI/Item/GHPickupWidget.h"
#include "Components/TextBlock.h"
#include "EnhancedInputComponent.h"
#include "Component/Inventory/GHInventoryComponent.h"

AGHPickupItem::AGHPickupItem()
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
	ItemSceneComp->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	// Movement Section
	RotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovementComp->RotationRate = FRotator(0.f, 45.f, 0.f);

	// Collision Section
	ItemCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	ItemCollisionComp->SetupAttachment(RootComponent);
	ItemCollisionComp->SetSphereRadius(150.f);
	ItemCollisionComp->SetCollisionProfileName(TEXT("ItemProfile"));
	ItemCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGHPickupItem::OnOverlapBegin);
	ItemCollisionComp->OnComponentEndOverlap.AddDynamic(this, &AGHPickupItem::OnEndOverlap);

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
	ID = FName("Cube");
	OnIDChanged.AddDynamic(this, &AGHPickupItem::HandleIDChanged);
}

void AGHPickupItem::BeginPlay()
{
	Super::BeginPlay();

	HandleIDChanged(ID);
}

void AGHPickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToPlayerInventory();
}

void AGHPickupItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* CollideCharacter = Cast<ACharacter>(OtherActor);
	Player = Cast<AGHPlayer>(CollideCharacter);
	if (IsValid(Player))
	{
		PickupWidgetComp->SetVisibility(true);
		PlayerPickupAction = Player->GetDropActionValue();
	}

}

void AGHPickupItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(Player))
	{
		PickupWidgetComp->SetVisibility(false);
		Player = nullptr;
		PlayerPickupAction = nullptr;
	}

}

void AGHPickupItem::HandleIDChanged(FName NewID)
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
	if (ItemData->ID == FName("Cube"))
	{
		ItemStaticMeshComp->SetRelativeScale3D(FVector(.5f, .5f, .5f));
	}
	if (ItemData->ID == FName("Sword"))
	{
		ItemStaticMeshComp->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
		ItemStaticMeshComp->SetRelativeLocation(FVector(0.f, 60.f, 70.f));
		ItemStaticMeshComp->SetRelativeRotation(FRotator(0.f, 0.f, 50.f));
	}
}

void AGHPickupItem::SetID(FName NewID)
{
	if (ID != NewID)
	{
		ID = NewID;
		OnIDChanged.Broadcast(ID);
	}
}

void AGHPickupItem::MoveToPlayerInventory()
{
	if (PlayerPickupAction)
	{
		if (PlayerPickupAction->GetValue().Get<bool>())
		{
			UGHInventoryComponent* Inventory = Player->GetInventory();
			bool isDrop = Inventory->Drop(ID, Quantity);

			if (isDrop)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, FString::Printf(TEXT("Drop %s (%d)"), *ID.ToString(), Quantity));
				Destroy();
			}
		}
	}
}