// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ETC/GHMainLevelCharacter.h"
#include "UI/Player/GHPlayerWidget.h"
#include "Components/Button.h"
#include "Controller/GHPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"

AGHMainLevelCharacter::AGHMainLevelCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// MainLevel Widget Section
	static ConstructorHelpers::FClassFinder<UGHPlayerWidget>
		MainLevelWidgetRef(TEXT("/Game/Gihoon/UI/WB_Main.WB_Main_C"));
	if (MainLevelWidgetRef.Succeeded())
	{
		MainLevelWidgetClass = MainLevelWidgetRef.Class;
	}

	GetCharacterMovement()->GravityScale = 0.0f;


}

void AGHMainLevelCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MainLevelWidgetClass))
	{
		MainLevelWidgetInstance = CreateWidget<UGHPlayerWidget>(GetWorld(), MainLevelWidgetClass);
		PlayBtn = Cast<UButton>(MainLevelWidgetInstance->GetWidgetFromName(TEXT("PlayBtn")));
		NothingBtn = Cast<UButton>(MainLevelWidgetInstance->GetWidgetFromName(TEXT("NothingBtn")));
		PlayBtn->OnClicked.AddDynamic(this, &AGHMainLevelCharacter::PlayBtnClicked);
		NothingBtn->OnClicked.AddDynamic(this, &AGHMainLevelCharacter::NothingBtnClicked);
	}

	// 플레이어 컨트롤러 타깃 변경
	AGHPlayerController* PlayerController = Cast<AGHPlayerController>(GetController());
	if (IsValid(PlayerController) && IsValid(MainLevelWidgetInstance))
	{
		// GameOver Widget 출력
		MainLevelWidgetInstance->AddToViewport();

		// 입력 타깃 변경 : Game -> GameOver Widget
		FInputModeUIOnly InputUIMode;
		InputUIMode.SetWidgetToFocus(MainLevelWidgetInstance->TakeWidget());
		PlayerController->SetInputMode(InputUIMode);
	}

	// 캐릭터의 카메라 각도 수정
	if (PlayerController)
	{
		//FRotator NewRotation = PlayerController->GetControlRotation();
		//NewRotation.Pitch = 40.0f;
		//PlayerController->SetControlRotation(NewRotation);
	}

}

void AGHMainLevelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGHMainLevelCharacter::PlayBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Play Btn Click"));

	// Level_01 로 이동
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level_01"));

	// 입력 타깃 변경 : GameOver Widget -> Game
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (PlayerController)
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(false);
		PlayerController->SetInputMode(InputMode);
	}
}

void AGHMainLevelCharacter::NothingBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Nothing Btn Click"));
}
