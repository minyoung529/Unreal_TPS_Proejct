// Fill out your copyright notice in the Description page of Project Settings.


#include "CloudPlatform.h"

// Sets default values
ACloudPlatform::ACloudPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetMesh(TEXT("/Script/Engine.StaticMesh'/Game/__MyMapAsset/Cloud/cloud_Mball.cloud_Mball'"));

	RootComponent = baseMesh;
	BindingOnHit();
}
