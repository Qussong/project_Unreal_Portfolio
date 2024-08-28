// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/GHPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/GHPlayerInputAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Controller/GHPlayerController.h"
#include "UI/Player/GHPlayerWidget.h"
#include "Components/ProgressBar.h"
#include "Stat/Player/GHPlayerStatComponent.h"
#include "Component/Inventory/GHInventoryComponent.h"

AGHPlayer::AGHPlayer()
{
	// Tick Section
	PrimaryActorTick.bCanEverTick = true;

	// Camera Section
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetWorldRotation(FRotator(-50.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 1400.f;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->FieldOfView = 55.f;

	// Capsule Section
	GetCapsuleComponent()->InitCapsuleSize(30.f, 90.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerProfile"));

	// Skeletal Mesh Section
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		PlayerMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Gihoon/UE_Characters/Mannequin_UE4/Meshes/SK_Mannequin_GH.SK_Mannequin_GH'"));
	if (PlayerMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(PlayerMeshRef.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	
	// AnimInstance Section
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		PlayerAnimClassRef(TEXT("/Game/Gihoon/Animations/Player/ABP_GHPlayer.ABP_GHPlayer_C"));
	if (PlayerAnimClassRef.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnimClassRef.Class);
	}

	// IMC Section
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		IMCRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Gihoon/Input/IMC_Player.IMC_Player'"));
	if (IMCRef.Succeeded())
	{
		IMC = IMCRef.Object;
	}

	// UI Section
	static ConstructorHelpers::FClassFinder<UGHPlayerWidget>
		PlayerWidgetRef(TEXT("/Game/Gihoon/UI/WB_Player.WB_Player_C"));
	if (PlayerWidgetRef.Succeeded())
	{
		PlayerWidgetClass = PlayerWidgetRef.Class;
	}

	// Stat Section
	Stat = CreateDefaultSubobject<UGHPlayerStatComponent>(TEXT("PlayerStat"));

	// Inventory Section
	Inventory = CreateDefaultSubobject<UGHInventoryComponent>(TEXT("Inventory"));

}

void AGHPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// UI Section
	if (IsValid(PlayerWidgetClass))
	{
		PlayerWidgetInstance = CreateWidget<UGHPlayerWidget>(GetWorld(), PlayerWidgetClass);
		UGHPlayerStatComponent* PlayerStat = Cast<UGHPlayerStatComponent>(Stat);
		if (IsValid(PlayerWidgetInstance) && IsValid(PlayerStat))
		{
			PlayerWidgetInstance->AddToViewport();

			PlayerWidgetInstance->GetHealthBar()->SetPercent(PlayerStat->GetCurrnetHealth() / PlayerStat->GetMaxHealth());
			PlayerWidgetInstance->GetManaBar()->SetPercent(PlayerStat->GetCurrentMana() / PlayerStat->GetMaxMana());
			PlayerWidgetInstance->GetStaminaBar()->SetPercent(PlayerStat->GetCurrentStamina() / PlayerStat->GetMaxStamina());
			PlayerWidgetInstance->GetEXPBar()->SetPercent(PlayerStat->GetCurrentEXP() / PlayerStat->GetMaxEXP());
		}
	}
}

void AGHPlayer::BeginPlay()
{
	Super::BeginPlay();

	// IMC Section
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(IMC, 0);
	}

}

void AGHPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGHPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	const UGHPlayerInputAction* PlayerInput = GetDefault<UGHPlayerInputAction>();
	if (IsValid(EnhancedInputComp) && IsValid(PlayerInput))
	{
		// Move
		EnhancedInputComp->BindAction(PlayerInput->IA_SetDestination, ETriggerEvent::Triggered, this, &AGHPlayer::IA_SetDestination_Triggered);
		EnhancedInputComp->BindAction(PlayerInput->IA_SetDestination, ETriggerEvent::Started, this, &AGHPlayer::IA_SetDestination_Started);
		EnhancedInputComp->BindAction(PlayerInput->IA_SetDestination, ETriggerEvent::Canceled, this, &AGHPlayer::IA_SetDestination_Canceled);
		EnhancedInputComp->BindAction(PlayerInput->IA_SetDestination, ETriggerEvent::Completed, this, &AGHPlayer::IA_SetDestination_Completed);
		// Item Slot
		EnhancedInputComp->BindAction(PlayerInput->IA_SlotNum1, ETriggerEvent::Started, this, &AGHPlayer::IA_SlotNum1_Started);
		// Drop
		DropActionValue = &EnhancedInputComp->BindActionValue(PlayerInput->IA_Drop);
		// Inventory
		EnhancedInputComp->BindAction(PlayerInput->IA_Inventory, ETriggerEvent::Started, this, &AGHPlayer::IA_Inventory_Started);
		// Equip
		EnhancedInputComp->BindAction(PlayerInput->IA_Equip, ETriggerEvent::Started, this, &AGHPlayer::IA_Equip_Started);

	}
}

void AGHPlayer::IA_SetDestination_Triggered(const FInputActionValue& Value)
{
	Cast<AGHPlayerController>(GetController())->GetLocationUnderCursor();
	Cast<AGHPlayerController>(GetController())->Follow();
}

void AGHPlayer::IA_SetDestination_Started(const FInputActionValue& Value)
{
	GetCharacterMovement()->StopMovementImmediately();
}

void AGHPlayer::IA_SetDestination_Canceled(const FInputActionInstance& Value)
{
}

void AGHPlayer::IA_SetDestination_Completed(const FInputActionInstance& Value)
{
	float ElapsedTime = Value.GetElapsedTime();

	if (ElapsedTime < 0.5f)
	{
		Cast<AGHPlayerController>(GetController())->MoveTo();
	}
}

void AGHPlayer::IA_PlayerAttack_Started(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Player Attack"));
}

void AGHPlayer::IA_SlotNum1_Started(const FInputActionValue& Value)
{
	if (IsValid(Stat))
	{
		Stat->DecreaseHealth(10.f);
		PlayerWidgetInstance->GetHealthBar()->SetPercent(Stat->GetCurrnetHealth() / Stat->GetMaxHealth());
	}

	UE_LOG(LogTemp, Log, TEXT("Slot Num1"));
}

void AGHPlayer::IA_Inventory_Started(const FInputActionInstance& Value)
{
	Inventory->ReviewInventory();
}

void AGHPlayer::IA_Equip_Started(const FInputActionInstance& Value)
{
	if (!isEquip)
	{
		if (Inventory->ArmedWeapon(FName("Sword")))
			isEquip = true;
	}
	else
	{
		if (Inventory->DisArmedWeapon())
			isEquip = false;
	}
}
