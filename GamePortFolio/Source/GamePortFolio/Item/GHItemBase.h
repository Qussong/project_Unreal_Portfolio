// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/GHItemStruct.h"
#include "GHItemBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIDDelegate, FName, NewID);

UCLASS()
class GAMEPORTFOLIO_API AGHItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AGHItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

// Data Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DataTable)
	TObjectPtr<UDataTable> ItemDataTable;

	FItemInventoryData* ItemData;

// Scene Comp Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Scene)
	TObjectPtr<USceneComponent> ItemSceneComp;

// Mesh Comp Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class USkeletalMeshComponent> ItemSkeletalMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> ItemStaticMeshComp;

// Movement Comp Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Move)
	TObjectPtr<class URotatingMovementComponent> RotatingMovementComp;

// Collision Comp Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SphereCollision)
	TObjectPtr<class USphereComponent> ItemCollisionComp;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ID)
	int32 Quantity = 1;

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
