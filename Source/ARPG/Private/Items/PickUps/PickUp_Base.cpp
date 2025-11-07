#include "Items/PickUps/PickUp_Base.h"

#include "Components/SphereComponent.h"

// Sets default values
APickUp_Base::APickUp_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);
	CollisionSphere->InitSphereRadius(50.f);
	CollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionSphereBeginOverlap);
}

void APickUp_Base::OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
