// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/GHBaseItem.h"
#include "GHEquipItem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHEquipItem : public AGHBaseItem
{
	GENERATED_BODY()

public:
	AGHEquipItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

// Collision Comp Section
//protected:
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SphereCollision)
//	TObjectPtr<class UBoxComponent> ItemCollisionComp;
//protected:
//	UFUNCTION()
//	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
//						AActor* OtherActor,
//						UPrimitiveComponent* OtherComp,
//						int32 OtherBodyIndex,
//						bool bFromSweep,
//						const FHitResult& SweepResult);
//	UFUNCTION()
//	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
//		AActor* OtherActor,
//		UPrimitiveComponent* OtherComp,
//		int32 OtherBodyIndex);

};
