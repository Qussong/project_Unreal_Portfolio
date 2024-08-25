// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
#include "UI/GHBaseWidget.h"
#include "GHPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API UGHPlayerWidget : public UGHBaseWidget
{
	GENERATED_BODY()

public:
	UGHPlayerWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HealthBar;
public:
	class UProgressBar* GetHealthBar() { return HealthBar; }

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> ManaBar;
public:
	class UProgressBar* GetManaBar() { return ManaBar; }

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> StaminaBar;
public:
	class UProgressBar* GetStaminaBar() { return StaminaBar; }

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> EXPBar;
public:
	class UProgressBar* GetEXPBar() { return EXPBar; }
	
};
