// Fill out your copyright notice in the Description page of Project Settings.

#include "CloudPlatform.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ACloudPlatform::ACloudPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetMesh(TEXT("/Script/Engine.StaticMesh'/Game/__MyMapAsset/Cloud/cloud_Mball.cloud_Mball'"));

	RootComponent = baseMesh;
	BindingOnHit();
}

void ACloudPlatform::OnBeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
	ChangPlatformState(VISIBLE_STATE::Predelay, preDelay);
}

void ACloudPlatform::OnTick()
{
	timer -= GetWorld()->GetDeltaSeconds();
	
	if (timer < 0.f)
	{
		switch (state)
		{
		case VISIBLE_STATE::Predelay:
			ChangPlatformState(VISIBLE_STATE::On, onTime);
			break;

		case VISIBLE_STATE::On:
			ChangPlatformState(VISIBLE_STATE::Off, offTime);
			break;

		case VISIBLE_STATE::Off:
			ChangPlatformState(VISIBLE_STATE::On, onTime);
			break;
		}
	}
}

void ACloudPlatform::VisibleOnState()
{
	baseMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndProbe);
	FVector white = FVector::One();
	baseMesh->SetVectorParameterValueOnMaterials(TEXT("Opacity"), white);
}

void ACloudPlatform::VisibleOffState()
{
	baseMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	FVector white = FVector::One() * 0.75f;
	baseMesh->SetVectorParameterValueOnMaterials(TEXT("Opacity"), white);
}

void ACloudPlatform::ChangPlatformState(VISIBLE_STATE visibleState, float time)
{
	state = visibleState;
	timer = time;

	if (state == VISIBLE_STATE::On)
	{
		VisibleOnState();
	}
	else if (state == VISIBLE_STATE::Off)
	{
		VisibleOffState();
	}
}
