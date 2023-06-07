#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenerateParticle.h"
#include "MyPlatform.generated.h"

UCLASS()
class AMyPlatform : public AActor
{
	GENERATED_BODY()

public:
	AMyPlatform();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;

public:
	virtual void Tick(float DeltaTime) override;


private:
	UGenerateParticle particleGenerator;

		// CHILD
protected:

	void SetMesh(const TCHAR* name);
	virtual void OnBeginPlay();
	virtual void OnTick();

protected:

};
