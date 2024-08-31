// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/GHPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

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

void AGHPlayerController::GetLocationUnderCursor()
{
	FHitResult HitResult;
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	isHit = GetHitResultUnderCursorByChannel(TraceType, true, HitResult);
	if (isHit)
	{
		Destination = HitResult.Location;	// 마우스 커서 충돌위치 = 목적지
	}
}

void AGHPlayerController::Follow()
{
	FVector From = GetPawn()->GetActorLocation();
	FVector To = Destination;
	FVector Direction = (To - From).GetSafeNormal();

	GetPawn()->AddMovementInput(Direction, 1.f, false);
}

void AGHPlayerController::MoveTo()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);

	UNiagaraSystem* NiagaraSystem = 
		LoadObject<UNiagaraSystem>(nullptr, TEXT("/Script/Niagara.NiagaraSystem'/Game/Gihoon/VFX/Cursor/FX_Cursor.FX_Cursor'"));
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, Destination);
}

void AGHPlayerController::Rotate()
{
	FVector From = GetPawn()->GetActorLocation();
	FVector To = Destination;
	FVector Direction = (To - From).GetSafeNormal();
	FRotator TargetRotation = Direction.Rotation();

	GetPawn()->SetActorRotation(FRotator(0.f, TargetRotation.Yaw, 0.f));

	UE_LOG(LogTemp, Log, TEXT("The float value is: %s"), *TargetRotation.ToString());
}
