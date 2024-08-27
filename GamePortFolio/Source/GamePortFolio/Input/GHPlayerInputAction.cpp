// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/GHPlayerInputAction.h"
#include "InputAction.h"

UGHPlayerInputAction::UGHPlayerInputAction()
{
	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputActionSetDestinationRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Gihoon/Input/Action/IA_SetDestination.IA_SetDestination'"));
	if (InputActionSetDestinationRef.Succeeded())
	{
		IA_SetDestination = InputActionSetDestinationRef.Object;
	}	
	
	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputActionPlayerAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Gihoon/Input/Action/IA_PlayerAttack.IA_PlayerAttack'"));
	if (InputActionPlayerAttackRef.Succeeded())
	{
		IA_PlayerAttack = InputActionPlayerAttackRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputActionSlotNum1Ref(TEXT("/Script/EnhancedInput.InputAction'/Game/Gihoon/Input/Action/IA_SlotNum1.IA_SlotNum1'"));
	if (InputActionSlotNum1Ref.Succeeded())
	{
		IA_SlotNum1 = InputActionSlotNum1Ref.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputActionDropRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Gihoon/Input/Action/IA_Drop.IA_Drop'"));
	if (InputActionDropRef.Succeeded())
	{
		IA_Drop = InputActionDropRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputActionInventoryRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Gihoon/Input/Action/IA_Inventory.IA_Inventory'"));
	if (InputActionInventoryRef.Succeeded())
	{
		IA_Inventory = InputActionInventoryRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputActionEquipRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Gihoon/Input/Action/IA_Equip.IA_Equip'"));
	if (InputActionEquipRef.Succeeded())
	{
		IA_Equip = InputActionEquipRef.Object;
	}
}
