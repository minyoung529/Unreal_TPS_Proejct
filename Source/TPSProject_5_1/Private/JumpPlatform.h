// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlatform.h"
#include "GameFramework/Actor.h"
#include "JumpPlatform.generated.h"

UCLASS()
class AJumpPlatform : public AMyPlatform
{
	GENERATED_BODY()
	
public:	
	AJumpPlatform();

protected:
	virtual void OnContactPlayer();
	virtual void OnBeginPlay();
};
