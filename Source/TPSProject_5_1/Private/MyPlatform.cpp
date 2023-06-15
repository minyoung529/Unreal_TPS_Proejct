#include "MyPlatform.h"
#include "C:\Program Files\Epic Games\UE\UE_5.1\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\EnhancedInputSubsystems.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

AMyPlatform::AMyPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = baseMesh;
}

void AMyPlatform::BeginPlay()
{
	OnBeginPlay();
}

void AMyPlatform::ContactPlayer()
{
	OnContactPlayer();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), enterEffect, baseMesh->GetComponentLocation(), baseMesh->GetComponentRotation());
}

void AMyPlatform::Tick(float DeltaTime)
{
	OnTick();
}

void AMyPlatform::SetMesh(const TCHAR *name)
{
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));

	baseMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshAsset(name);

	if (BaseMeshAsset.Succeeded())
	{
		baseMesh->SetStaticMesh(BaseMeshAsset.Object);
	}
}

void AMyPlatform::OnBeginPlay() {}
void AMyPlatform::OnTick() {}
void AMyPlatform::OnContactPlayer() {}

void AMyPlatform::BindingOnHit()
{
    baseMesh->OnComponentHit.AddDynamic(this, &AMyPlatform::OnHit);
}

void AMyPlatform::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	OnContactPlayer();
}