// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinPlatform.h"
#include "MyPlatform.h"
#include "TPSCharacter.h"
#include "Kismet/GameplayStatics.h"
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
	if(!isClearPlatform)return;
	if(isClear)return;
	
	APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (player)
	{
		ATPSCharacter *character = Cast<ATPSCharacter>(player);
		if (character)
		{
			character->Clear();
			isClear=true;
		}
	}
}

void ACoinPlatform::OnBeginPlay()
{
	BindingOnHit();
}
