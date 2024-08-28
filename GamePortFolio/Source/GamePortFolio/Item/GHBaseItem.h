// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GHBaseItem.generated.h"

UCLASS()
class GAMEPORTFOLIO_API AGHBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AGHBaseItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

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
public:
	FORCEINLINE USkeletalMeshComponent* GetItemSkeletalMeshComp() { return ItemSkeletalMeshComp; }
	FORCEINLINE UStaticMeshComponent* GetItemStaticMeshComp() { return ItemStaticMeshComp; }

};
