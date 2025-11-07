#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp_Base.generated.h"

class USphereComponent;

UCLASS()
class ARPG_API APickUp_Base : public AActor
{
	GENERATED_BODY()

public:
	APickUp_Base();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="A_MY|Pick Up Interaction")
	USphereComponent* CollisionSphere;

	UFUNCTION()
	virtual void OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
