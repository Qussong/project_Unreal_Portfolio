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

// HealthBar Section
protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HealthBar;
public:
	class UProgressBar* GetHealthBar() { return HealthBar; }

// ManaBar Section
protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> ManaBar;
public:
	class UProgressBar* GetManaBar() { return ManaBar; }

// StaminaBar Section
protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> StaminaBar;
public:
	class UProgressBar* GetStaminaBar() { return StaminaBar; }

// EXPBar Section
protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> EXPBar;
public:
	class UProgressBar* GetEXPBar() { return EXPBar; }

// Health TextBlock Section
protected:
	UPROPERTY()
	TObjectPtr<class UTextBlock> CurHealthTextBlock;
	UPROPERTY()
	TObjectPtr<class UTextBlock> MaxHealthTextBlock;
public:
	class UTextBlock* GetCurHealthTextBlock() { return CurHealthTextBlock; }
	class UTextBlock* GetMaxHealthTextBlock() { return MaxHealthTextBlock; }

// Mana TextBlock Section
protected:
	UPROPERTY()
	TObjectPtr<class UTextBlock> CurManaTextBlock;
	UPROPERTY()
	TObjectPtr<class UTextBlock> MaxManaTextBlock;
public:
	class UTextBlock* GetCurManaTextBlock() { return CurManaTextBlock; }
	class UTextBlock* GetMaxManaTextBlock() { return MaxManaTextBlock; }

};
