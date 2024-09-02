// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GHCharacterBase.h"
#include "GHMainLevelCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPORTFOLIO_API AGHMainLevelCharacter : public AGHCharacterBase
{
	GENERATED_BODY()
	
public:
	AGHMainLevelCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

// Main Level Widget Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UGHPlayerWidget> MainLevelWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<class UGHPlayerWidget> MainLevelWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<class UButton> PlayBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<class UButton> NothingBtn;
protected:
	UFUNCTION()
	void PlayBtnClicked();

	UFUNCTION()
	void NothingBtnClicked();
};
