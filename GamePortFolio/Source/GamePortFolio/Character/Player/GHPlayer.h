// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GHCharacterBase.h"
#include "InputActionValue.h"
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

// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> IMC;	// Input Mapping Context

protected:
	void IA_SetDestination_Triggered(const FInputActionValue& Value);
	void IA_SetDestination_Started(const FInputActionValue& Value);
	void IA_SetDestination_Canceled(const FInputActionValue& Value);
	void IA_SetDestination_Completed(const FInputActionValue& Value);

	void IA_PlayerAttack_Started(const FInputActionValue& Value);

};
