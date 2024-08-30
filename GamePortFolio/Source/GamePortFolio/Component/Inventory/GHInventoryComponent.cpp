// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/GHInventoryComponent.h"
#include "Character/Player/GHPlayer.h"
#include "Components/ChildActorComponent.h"
#include "Item/GHBaseItem.h"

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

bool UGHInventoryComponent::Drop(FName ID, EItemInventoryType ItenType, int32 Quantity)
{
	// Data Table 에 해당 아이템에 대한 정보가 존재하는지 확인 및 수량 설정
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

	// 장비 타입 아이템을 얻게되면 플레이어에 해당 정보 넘겨줌
	if (ItenType == EItemInventoryType::ARMOR
		|| ItenType == EItemInventoryType::WEAPON)

	{
		Cast<AGHPlayer>(GetOwner())->AddChildActorMap(ID, nullptr);
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

bool UGHInventoryComponent::Armed(FName ID)
{
	// DataTable 로 부터 ID 에 해당하는 정보 얻어옴
	FItemInventoryData* ItemData = Items.Find(ID);
	if (nullptr == ItemData) return false;

	// Data 로 부터 장착과 관련된 정보 얻어옴
	FItemHoldableData HoldableData = ItemData->HoldableSettings;
	if (nullptr == HoldableData.EquipmentClass) return false;

	EquipChildComp = Cast<AGHPlayer>(GetOwner())->FindChildActorMap(ID);
	// ID에 해당하는 Child Actor Comp 가 Player에 저장되어 있지 않은경우
	if (nullptr == EquipChildComp)
	{
		if (false == CreateEquipmentComp(HoldableData))
			return false;

		if (false == SetEquipChildComp(ItemData))
			return false;

		// Player 에 추가된 ChildActorComp 에 대한 정보 저장
		Cast<AGHPlayer>(GetOwner())->AddChildActorMap(ID, EquipChildComp);
	}
	// ID에 해당하는 Child Actor Comp 가 Player에 저장되어 있는 경우
	else
	{
		// 생성된 Child Actor Component 를 월드에 등록
		EquipChildComp->RegisterComponent();
	}

	// ID 에 해당하는 Child Actor Comp 에 대한 작업을 마쳤기에 비워줌
	EquipChildComp = nullptr;

	return true;
}

bool UGHInventoryComponent::DisArmed(FName ID)
{
	EquipChildComp = Cast<AGHPlayer>(GetOwner())->FindChildActorMap(ID);
	if (IsValid(EquipChildComp))
	{
		EquipChildComp->UnregisterComponent();
		EquipChildComp = nullptr;

		return true;
	}

	return false;
}

bool UGHInventoryComponent::CreateEquipmentComp(FItemHoldableData& HoldableData)
{
	// Child Actor Component 생성
	EquipChildComp = NewObject<UChildActorComponent>(this, UChildActorComponent::StaticClass(), TEXT("DynamicChildActorComp"));
	if (nullptr == EquipChildComp) return false;

	// 부모 컴포넌트(SkeletalMesh)에 부착
	EquipChildComp->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, HoldableData.SocketName);
	// Child Actor Class 설정
	EquipChildComp->SetChildActorClass(HoldableData.EquipmentClass);
	// 초기 트랜스폼 설정
	EquipChildComp->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	// 생성된 Child Actor Component 를 월드에 등록
	EquipChildComp->RegisterComponent();

	return true;
}

bool UGHInventoryComponent::SetEquipChildComp(FItemInventoryData* ItemData)
{
	// 생성된 Child Actor에 접근
	AActor* SpawnedChildActor = Cast<AActor>(EquipChildComp->GetChildActor());
	if (nullptr == SpawnedChildActor) return false;

	if (nullptr != ItemData->PickupStaticMesh)
	{
		// Skeletal Mesh
		USkeletalMeshComponent* SkeletalMeshComp = Cast<AGHBaseItem>(SpawnedChildActor)->GetItemSkeletalMeshComp();
		if (IsValid(SkeletalMeshComp))
			SkeletalMeshComp->SetSkeletalMesh(ItemData->PickupSkeletalMesh.Get());

		// Static Mesh
		UStaticMeshComponent* StaticMeshComp = Cast<AGHBaseItem>(SpawnedChildActor)->GetItemStaticMeshComp();
		if (IsValid(StaticMeshComp))
			StaticMeshComp->SetStaticMesh(ItemData->PickupStaticMesh.Get());

	}

	return true;
}