// Fill out your copyright notice in the Description page of Project Settings.

#include "JumpPlatform.h"
#include "TPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AJumpPlatform::AJumpPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetMesh(TEXT("/Script/Engine.StaticMesh'/Game/__MyMapAsset/Breakast/BUBBLES_BUCKS_BREAKFAST_LOOP_CEREAL_NUTELLA_CEREAL_MILK.BUBBLES_BUCKS_BREAKFAST_LOOP_CEREAL_NUTELLA_CEREAL_MILK'"));
}

void AJumpPlatform::OnContactPlayer()
{
	APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (player)
	{
		ATPSCharacter *character = Cast<ATPSCharacter>(player);
		if (character)
		{
			character->PlatformJump();
		}
	}
	else
	{
	}
}

void AJumpPlatform::OnBeginPlay()
{
	BindingOnHit();
}
