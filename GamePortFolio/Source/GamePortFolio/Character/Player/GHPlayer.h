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

// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent>	CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent>	FollowCamera;

// UI Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UGHPlayerWidget> PlayerWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<class UGHPlayerWidget> PlayerWidgetInstance;

// Inventory Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TObjectPtr<class UGHInventoryComponent> Inventory;
public:
	FORCEINLINE UGHInventoryComponent* GetInventory() { return Inventory; }

// IMC Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> IMC;	// Input Mapping Context

// IA_SetDestination Section
protected:
	void IA_SetDestination_Triggered(const FInputActionValue& Value);
	void IA_SetDestination_Started(const FInputActionValue& Value);
	void IA_SetDestination_Canceled(const FInputActionInstance& Value);
	void IA_SetDestination_Completed(const FInputActionInstance& Value);

// IA_PlayerAttack Section
protected:
	void IA_PlayerAttack_Started(const FInputActionValue& Value);

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
	void IA_Inventory_Started(const FInputActionInstance& Value);

};
