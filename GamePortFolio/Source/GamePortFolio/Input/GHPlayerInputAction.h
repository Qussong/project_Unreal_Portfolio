// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GHPlayerInputAction.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHPlayerInputAction : public UObject
{
	GENERATED_BODY()
	
public:
	UGHPlayerInputAction();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_SetDestination;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_PlayerAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_SlotNum1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Drop;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Equip;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_NormalAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Run;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> IA_Roll;

};
