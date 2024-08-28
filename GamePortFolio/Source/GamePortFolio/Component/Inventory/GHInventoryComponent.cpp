// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/GHInventoryComponent.h"
#include "Character/Player/GHPlayer.h"
#include "Components/ChildActorComponent.h"

UGHInventoryComponent::UGHInventoryComponent()
{
	// DataTable Section
	static ConstructorHelpers::FObjectFinder<UDataTable>
		ItemDataTableRef(TEXT("/Script/Engine.DataTable'/Game/Gihoon/Item/Data/DT_InventoryItem.DT_InventoryItem'"));
	if (ItemDataTableRef.Succeeded())
	{
		ItemDataTable = ItemDataTableRef.Object;
	}
}

bool UGHInventoryComponent::Drop(FName ID, int32 Quantity)
{
	AActor* OwnweActor = GetOwner();
	AGHPlayer* Player = Cast<AGHPlayer>(OwnweActor);

	if (!CheckItemExist(ID, Quantity)) return false;

	FItemInventoryData* Item = Items.Find(ID);
	if (nullptr != Item)
	{
		// 이미 가지고 있는 경우
		int32 NewQuantity = Item->Quantity + DropItem.Quantity;
		DropItem.Quantity = NewQuantity;
		Items.Add(ID, DropItem);
	}
	else
	{
		// 처음 습득하는 경우
		Items.Add(ID, DropItem);
	}

	// 획득 아이템 정보 초기화
	DropItem = {};

	return true;
}

bool UGHInventoryComponent::CheckItemExist(FName ID, int32 NewQuantity)
{
	FItemInventoryData* Item = ItemDataTable->FindRow<FItemInventoryData>(ID, TEXT(""));
	if (nullptr == Item) return false;

	DropItem = *Item;
	if (NewQuantity != -1)
	{
		DropItem.Quantity = NewQuantity;
	}

	return true;;
}

void UGHInventoryComponent::ReviewInventory()
{
	if (Items.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Inventory Empty!"));
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("===================="));
	for (const TPair<FName, FItemInventoryData>& Item : Items)
	{
		FText Name = Item.Value.DisplayName;
		int32 Quantity = Item.Value.Quantity;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("%s : %d"), *Name.ToString(), Quantity));
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("==== Inventory List ===="));
}

bool UGHInventoryComponent::ArmedWeapon(FName ID)
{
	FItemInventoryData* ItemData = Items.Find(ID);
	if (nullptr == ItemData) return false;

	FItemHoldableData HoldableData = ItemData->HoldableSettings;
	if (nullptr == HoldableData.EquipmentClass) return false;

	if (nullptr == NewChildActorComp)
	{
		NewChildActorComp = NewObject<UChildActorComponent>(this, UChildActorComponent::StaticClass(), TEXT("DynamicChildActorComp"));
		if (nullptr == NewChildActorComp) return false;

		// 생성된 컴포넌트를 월드에 등록
		NewChildActorComp->RegisterComponent();
		// 부모 컴포넌트(SkeletalMesh)에 부착
		NewChildActorComp->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, HoldableData.SocketName);
		// Child Actor Class 설정
		NewChildActorComp->SetChildActorClass(HoldableData.EquipmentClass);
		// 초기 트랜스폼 설정
		NewChildActorComp->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

		// 생성된 Child Actor에 접근해서 로직을 추가
		AActor* SpawnedChildActor = Cast<AActor>(NewChildActorComp->GetChildActor());
		if (SpawnedChildActor)
		{
			if (nullptr != ItemData->PickupStaticMesh)
			{
				//SpawnedChildActor->GetMesh()
			}
		}

		return true;
	}
	else
	{
		NewChildActorComp->RegisterComponent();
		return true;
	}

	return false;
}

bool UGHInventoryComponent::DisArmedWeapon()
{
	if (IsValid(NewChildActorComp))
	{
		NewChildActorComp->UnregisterComponent();
		return true;
	}

	return false;
}
