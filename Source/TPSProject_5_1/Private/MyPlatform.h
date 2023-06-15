#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "MyPlatform.generated.h"

UCLASS()
class AMyPlatform : public AActor
{
	GENERATED_BODY()

public:
	AMyPlatform();

protected:\
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void ContactPlayer();

	// CHILD
protected:
	void SetMesh(const TCHAR *name);
	virtual void OnBeginPlay();
	virtual void OnTick();
	virtual void OnContactPlayer();
	void BindingOnHit();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent *baseMesh;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	class UNiagaraSystem *enterEffect;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
};
