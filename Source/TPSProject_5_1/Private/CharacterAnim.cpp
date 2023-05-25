// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnim.h"
#include "TPSCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

void UCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 소유 폰 얻어 오기
	auto ownerPawn = TryGetPawnOwner();

	// 플레이어로 캐스팅
	auto player = Cast<ATPSCharacter>(ownerPawn);

	if (player)
	{
		FVector velocity = player->GetVelocity();
		FVector forward = player->GetActorForwardVector();
		speed = FVector::DotProduct(forward, velocity);

		FVector right = player->GetActorRightVector();
		direction = FVector::DotProduct(right, velocity);

		auto movement = player->GetCharacterMovement();
		if (movement)
			isInAir = movement->IsFalling();
	}
}

void UCharacterAnim::PlayAttackAnim()
{
	//Montage_Play(attackAnimMontage);
}
