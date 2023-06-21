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
	Super::BeginPlay();
	effectTimer = 0.f;
	PrimaryActorTick.bCanEverTick = true;
	OnBeginPlay();
}

void AMyPlatform::ContactPlayer()
{
	OnContactPlayer();
}

void AMyPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnTick();

	if (effectTimer > 0.f)
	{
		effectTimer -= GetWorld()->GetDeltaSeconds();
	}
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
	if (effectTimer <= 0.f)
	{
		if (enterEffect != nullptr)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), enterEffect, GetActorLocation() + effectOffset, baseMesh->GetComponentRotation());
		}
		
		effectTimer = 0.3f;
	}

	OnContactPlayer();
}