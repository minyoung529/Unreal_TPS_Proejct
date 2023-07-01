// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMovePlatform.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyMovePlatform::AMyMovePlatform()
{
	plusDirection = true;

	SetMesh(TEXT("/Script/Engine.StaticMesh'/Game/__MyMapAsset/unicorn-milk/source/carton_milk_.carton_milk_'"));
}

void AMyMovePlatform::OnBeginPlay()
{
	direction = direction.GetSafeNormal(1.f);
	BindingOnHit();
	PrimaryActorTick.bCanEverTick = true;
}

void AMyMovePlatform::OnTick()
{
	FVector dir = (plusDirection) ? direction : -direction;
	FVector movement = dir * speed * GetWorld()->GetDeltaSeconds();
	float size = movement.Size();

	curDistance -= size;

	SetActorLocation(GetActorLocation() + movement);

	if (curDistance <= 0.0f)
	{
		plusDirection = !plusDirection;
		curDistance = distance;
	}
}

void AMyMovePlatform::OnContactPlayer()
{
	// if (overPlatform == 1)
	if(distance > 9000.f)
	{
		UGameplayStatics::OpenLevel(this, TEXT("TPSMap"));
	}
}
