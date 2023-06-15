// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinPlatform.h"
#include "MyPlatform.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ACoinPlatform::ACoinPlatform() : AMyPlatform()
{
	SetMesh(TEXT("/Script/Engine.StaticMesh'/Game/__MyMapAsset/Coin/CoinModel.CoinModel'"));
	baseMesh->SetRelativeScale3D(scale);

	RootComponent = baseMesh;
}

void ACoinPlatform::OnContactPlayer()
{
	// Niagara 시스템 생성
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), enterEffect, GetActorLocation());
}

void ACoinPlatform::OnBeginPlay()
{
	BindingOnHit();
}
