// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlatform.h"
#include "GameFramework/Actor.h"
#include "CloudPlatform.generated.h"

UCLASS()
class ACloudPlatform : public AMyPlatform
{
	GENERATED_BODY()

public:
	ACloudPlatform();

protected:
	virtual void OnBeginPlay() override;
	virtual void OnTick() override;

public:
	UPROPERTY(EditAnywhere, Category = Visible)
	float onTime;
	UPROPERTY(EditAnywhere, Category = Visible)
	float offTime;
	UPROPERTY(EditAnywhere, Category = Visible)
	float preDelay;

	enum class VISIBLE_STATE
	{
		None,
		Predelay,
		Off,
		On
	};

private:
	float timer;

	VISIBLE_STATE state = VISIBLE_STATE::None;

	void ChangPlatformState(VISIBLE_STATE visibleState, float time);

	void VisibleOnState();
	void VisibleOffState();
};
