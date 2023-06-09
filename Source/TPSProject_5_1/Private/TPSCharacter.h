// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C:\Program Files\Epic Games\UE\UE_5.1\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\InputActionValue.h"
#include "TPSCharacter.generated.h"

UCLASS()
class ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

public:
	void MoveForward(const FInputActionValue &Value);
	void MoveRight(const FInputActionValue &Value);
	void TurnPitch(const FInputActionValue &Value);
	void TurnYaw(const FInputActionValue &Value);

	void PlatformJump();

	void Clear();

public:
	// �ȱ� �ӵ�
	float walkSpeed = 200;
	// �޸��� �ӵ�
	float runSpeed = 600;
	float firstJumpZVelocity;

#pragma region /* Component*/
public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent *springArmComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent *tpsCamComp;
#pragma endregion

public:
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> victoryUIFactory;
public:
	// �������� UI ���� �ν��Ͻ�
	class UUserWidget *victoryUI;

#pragma region Input
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext *tpsMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *moveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *moveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *turnPitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *turnYawAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *jumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *fireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *grenadeGunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *sniperGunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *sniperZoominAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *runAction;
#pragma endregion

	virtual void OnJumped_Implementation() override;
};
