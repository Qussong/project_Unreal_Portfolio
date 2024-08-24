// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/GHPlayerController.h"

AGHPlayerController::AGHPlayerController()
{

}

void AGHPlayerController::BeginPlay()
{
	Super::BeginPlay();

    // Mouse Cursor Section (마우스 커서 표시)
    bShowMouseCursor = IsShowMouseCursor;
    bEnableClickEvents = IsEnableClickEvents;
    bEnableMouseOverEvents = IsEnableMouseOverEvents;

}
