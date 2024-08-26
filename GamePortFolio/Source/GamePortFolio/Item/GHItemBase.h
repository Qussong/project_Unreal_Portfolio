// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GHItemBase.generated.h"

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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemComponent")
	TObjectPtr<class USphereComponent> ItemCollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemComponent")
	TObjectPtr<class UStaticMeshComponent> ItemStaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemComponent")
	TObjectPtr<class USkeletalMeshComponent> ItemSkeletalMeshComp;

// Collision Overlap Section
protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

// Data Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DataTable)
	TObjectPtr<UDataTable> ItemDataTable;
	
public:


};
