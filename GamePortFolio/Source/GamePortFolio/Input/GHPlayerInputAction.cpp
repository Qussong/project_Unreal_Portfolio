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

}
