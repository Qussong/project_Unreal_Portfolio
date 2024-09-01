// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GHCharacterBase.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "GHPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHPlayer : public AGHCharacterBase
{
	GENERATED_BODY()
	
public:
	AGHPlayer();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Anim Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim)
	TObjectPtr<class UGHPlayerAnim> Anim;

// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent>	CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent>	FollowCamera;

// Death Section
protected:
	virtual void SetDeath() override;

// UI Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UGHPlayerWidget> PlayerWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<class UGHPlayerWidget> PlayerWidgetInstance;
protected:
	void UpdateUI();

// Inventory Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TObjectPtr<class UGHInventoryComponent> Inventory;
public:
	FORCEINLINE UGHInventoryComponent* GetInventory() { return Inventory; }

// Equip Seciton
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ChildActorComp)
	TMap<FName, UChildActorComponent*> ChildActorMap;
public:
	UChildActorComponent* FindChildActorMap(FName Name);
	void AddChildActorMap(FName Name, UChildActorComponent* ChildActor);

// IMC Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> IMC;	// Input Mapping Context

// IA_SetDestination Section
protected:
	struct FEnhancedInputActionValueBinding* MoveActionValue;
	void IA_SetDestination_Triggered(const FInputActionValue& Value);
	void IA_SetDestination_Started(const FInputActionValue& Value);
	void IA_SetDestination_Canceled(const FInputActionInstance& Value);
	void IA_SetDestination_Completed(const FInputActionInstance& Value);
public:
	FEnhancedInputActionValueBinding* GetMoveActionValue() { return MoveActionValue; }

// IA_Slot Section
protected:
	void IA_SlotNum1_Started(const FInputActionValue& Value);

// IA_Drop
protected:
	struct FEnhancedInputActionValueBinding* DropActionValue;
public:
	FEnhancedInputActionValueBinding* GetDropActionValue() { return DropActionValue; }

// IA_Inventory
protected:
	void IA_Inventory_Started(const FInputActionValue& Value);

// IA_Equip
protected:
	void IA_Equip_Started(const FInputActionValue& Value);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equip)
	bool isEquip = false;	// 장비 장착 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	bool isCombat = false;	// 전투 상태 여부

// IA_Normal Attack
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hit)
	TSet<AActor*> HitCheckContainer;
protected:
	void IA_NormalAttack_Started(const FInputActionValue& Value);
public:
	void AttackCheck_Begin(FVector& Start_V, FVector End_V, FVector& Start_H, FVector& End_H);
	void AttackCheck_Tick(FVector& Start_V, FVector End_V, FVector& Start_H, FVector& End_H);

// Hit Section
protected:
	void EnemyHit(TArray<FHitResult>& HitResults);
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
