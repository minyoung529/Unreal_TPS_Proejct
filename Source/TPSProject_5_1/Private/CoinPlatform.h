// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlatform.h"
#include "CoinPlatform.generated.h"

UCLASS()
class ACoinPlatform : public AMyPlatform
{
	GENERATED_BODY()

public:
	ACoinPlatform();

public:
	UPROPERTY(EditDefaultsOnly, Category = Transform)
	FVector scale = FVector(0.1f, 0.1f, 0.1f);

	UPROPERTY(EditAnywhere, Category = Clear)
	bool isClearPlatform = false;

	bool isClear = false;

protected:
	virtual void OnBeginPlay();
	virtual void OnContactPlayer();
};
