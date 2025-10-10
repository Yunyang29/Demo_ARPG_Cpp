#include "Items/Projectile_Base.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
#include "FunctionLibrary_Base.h"
#include "GameplayTags_Base.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile_Base::AProjectile_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block); // 
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectHit); // ?
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);

	ProjectileNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	ProjectileNiagaraComp->SetupAttachment(GetRootComponent());

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	ProjectileMovementComp->InitialSpeed = 700.f;
	ProjectileMovementComp->MaxSpeed = 900.f;
	ProjectileMovementComp->Velocity = FVector(1.f, 0, 0);
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;
}

void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();
	if (ProjectileDamagePolicy == EProjectileMovementMode::OnBeginOverlap)
	{
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void AProjectile_Base::OnProjectHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);

	APawn* HitPawn = Cast<APawn>(OtherActor);
	if (!HitPawn || !UFunctionLibrary_Base::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}

	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UFunctionLibrary_Base::NativeDoesActorHaveTag(HitPawn, GameplayTags_Base::Player_Status_Blocking);
	if (bIsPlayerBlocking)
	{
		bIsValidBlock = UFunctionLibrary_Base::IsValidBlock(this, HitPawn);
	}

	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = HitPawn;
	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitPawn, GameplayTags_Base::Player_Event_SuccessfulBlock, EventData);
	}
	else
	{
		// UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GameplayTags_Base::Shared_Event_MeleeHit, EventData);
	}
	Destroy();
}

void AProjectile_Base::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
