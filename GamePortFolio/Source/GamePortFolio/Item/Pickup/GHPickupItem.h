// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/GHBaseItem.h"
#include "Item/GHItemStruct.h"
#include "GHPickupItem.generated.h"

// ID 변경시 바인딩된 함수 호출
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIDDelegate, FName, NewID);

UCLASS()
class GAMEPORTFOLIO_API AGHPickupItem : public AGHBaseItem
{
	GENERATED_BODY()
	
public:	
	AGHPickupItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

// Data Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DataTable)
	TObjectPtr<UDataTable> ItemDataTable;

	FItemInventoryData* ItemData;

// Movement Comp Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Move)
	TObjectPtr<class URotatingMovementComponent> RotatingMovementComp;

// Collision Comp Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SphereCollision)
	TObjectPtr<class USphereComponent> ItemCollisionComp;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
					  AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex);

// ID Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FName ID;	// 아이디

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Quantity = 1;	// 수량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EItemInventoryType ItemType;	// 타입

	UPROPERTY()
	FIDDelegate OnIDChanged;

	UFUNCTION()
	void HandleIDChanged(FName NewID);

public:
	void SetID(FName NewID);
	FORCEINLINE void SetQuantity(int32 NewQuantity) { Quantity = NewQuantity; }

// UI Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<class UGHItemWidgetComponent> PickupWidgetComp;

// Pickup Section
protected:
	TObjectPtr<class AGHPlayer> Player;
	struct FEnhancedInputActionValueBinding* PlayerPickupAction;

// Drop Section
protected:
	void MoveToPlayerInventory();
};
