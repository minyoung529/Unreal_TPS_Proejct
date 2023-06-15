// Fill out your copyright notice in the Description page of Project Settings.

#include "TPSCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "C:\Program Files\Epic Games\UE\UE_5.1\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\EnhancedInputSubsystems.h"
#include "C:\Program Files\Epic Games\UE\UE_5.1\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\EnhancedInputComponent.h"
#include "Bullet.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyFSM.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "CharacterAnim.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
	// ���̷�Ż�޽� ������ �ε�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/__MyCharacter/Bot/Mesh/SK_Bot.SK_Bot'"));

	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	// ī�޶��� �θ� ������Ʈ ����
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if (springArmComp)
	{
		springArmComp->SetupAttachment(RootComponent);
		springArmComp->SetRelativeLocation(FVector(0, 0, 60));
		springArmComp->TargetArmLength = 400;
	}

	// ī�޶� ������Ʈ
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamComp"));
	if (tpsCamComp)
	{
		tpsCamComp->SetupAttachment(springArmComp);
	}

	// 2�� ����
	JumpMaxCount = 2;
}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	firstJumpZVelocity = GetCharacterMovement()->JumpZVelocity;

	// �������� UI ���� �ν��Ͻ� ����
	sniperUI = CreateWidget(GetWorld(), sniperUIFactory);

	// ũ�ν���� UI ���� �ν��Ͻ� ����
	crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);

	// ũ�ν���� UI ���
	crosshairUI->AddToViewport();
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController *PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(tpsMappingContext, 0);
		}
	}

	// ��ǲ �׼� ���ε�
	UEnhancedInputComponent *EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComp)
	{
		// MoveForward
		EnhancedInputComp->BindAction(moveForwardAction, ETriggerEvent::Triggered, this, &ATPSCharacter::MoveForward);

		// MoveRight
		EnhancedInputComp->BindAction(moveRightAction, ETriggerEvent::Triggered, this, &ATPSCharacter::MoveRight);

		// TurnPitch
		EnhancedInputComp->BindAction(turnPitchAction, ETriggerEvent::Triggered, this, &ATPSCharacter::TurnPitch);

		// TurnYaw
		EnhancedInputComp->BindAction(turnYawAction, ETriggerEvent::Triggered, this, &ATPSCharacter::TurnYaw);

		// Jump
		EnhancedInputComp->BindAction(jumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComp->BindAction(jumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// InputFire
		// EnhancedInputComp->BindAction(fireAction, ETriggerEvent::Triggered, this, &ATPSCharacter::InputFire);

		// GrenadeGun
		// EnhancedInputComp->BindAction(grenadeGunAction, ETriggerEvent::Triggered, this, &ATPSCharacter::ChangeToGrenadeGun);

		// SniperGun
		// EnhancedInputComp->BindAction(sniperGunAction, ETriggerEvent::Triggered, this, &ATPSCharacter::ChangeToSniperGun);

		// SniperZoomin
		// EnhancedInputComp->BindAction(sniperZoominAction, ETriggerEvent::Triggered, this, &ATPSCharacter::SniperZoomin);

		// RunAction
		EnhancedInputComp->BindAction(runAction, ETriggerEvent::Triggered, this, &ATPSCharacter::InputRun);
	}
}

void ATPSCharacter::MoveForward(const FInputActionValue &Value)
{
	float Movement = Value.Get<float>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDir, Movement);
	}
}

void ATPSCharacter::MoveRight(const FInputActionValue &Value)
{
	float Movement = Value.Get<float>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDir, Movement);
	}
}

void ATPSCharacter::TurnPitch(const FInputActionValue &Value)
{
	float Turn = -(Value.Get<float>());
	if (Controller != nullptr)
	{
		AddControllerPitchInput(Turn);
	}
}

void ATPSCharacter::TurnYaw(const FInputActionValue &Value)
{
	float Turn = Value.Get<float>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(Turn);
	}
}

void ATPSCharacter::InputRun(const FInputActionValue &Value)
{
	auto movement = GetCharacterMovement();
	if (movement == nullptr)
		return;

	bool isRun = Value.Get<bool>();
	if (isRun)
	{
		movement->MaxWalkSpeed = runSpeed;
	}
	else
	{
		movement->MaxWalkSpeed = walkSpeed;
	}
}

void ATPSCharacter::OnJumped_Implementation()
{
	GetCharacterMovement()->JumpZVelocity = firstJumpZVelocity;
}

void ATPSCharacter::PlatformJump()
{
	GetCharacterMovement()->JumpZVelocity= firstJumpZVelocity * 2.75f;
	ACharacter::Jump();
}