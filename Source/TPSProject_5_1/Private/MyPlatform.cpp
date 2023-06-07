#include "MyPlatform.h"
#include "C:\Program Files\Epic Games\UE\UE_5.1\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\EnhancedInputSubsystems.h"
#include <Kismet/GameplayStatics.h>

AMyPlatform::AMyPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlatform::BeginPlay()
{
	OnBeginPlay();
}

void AMyPlatform::Tick(float DeltaTime)
{
	OnTick();
}

void AMyPlatform::SetMesh(const TCHAR *name)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(name);

	if (tempMesh.Succeeded())
	{
		// GetMesh()->SetStaticMesh(tempMesh.Object);
	}
}

void AMyPlatform::NotifyActorBeginOverlap(AActor *otherActor)
{
	//UE_LOG(LogTemp, Log, otherActor->name);
}