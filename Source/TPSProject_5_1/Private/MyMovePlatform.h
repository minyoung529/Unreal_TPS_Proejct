// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlatform.h"
#include "MyMovePlatform.generated.h"

UCLASS()
class AMyMovePlatform : public AMyPlatform
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyMovePlatform();

	UPROPERTY(EditAnywhere, Category = Move)
	FVector direction;

	UPROPERTY(EditAnywhere, Category = Move)
	float distance = 1.f;

	UPROPERTY(EditAnywhere, Category = Move)
	float speed = 1.f;

protected:
	virtual void OnBeginPlay();
	virtual void OnTick() override;
	virtual void OnContactPlayer() override;


private:
	bool plusDirection = true;
	float curDistance;
};
