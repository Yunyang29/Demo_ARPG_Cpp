#include "Items/Projectile_Base.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "FunctionLibrary_Base.h"
#include "GameplayTags_Base.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile_Base::AProjectile_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	SetRootComponent(CollisionBoxComp);
	CollisionBoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block); // 
	CollisionBoxComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionBoxComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionBoxComp->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectHit); // ?
	CollisionBoxComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetupAttachment(GetRootComponent());

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 700.f;
	MovementComp->MaxSpeed = 900.f;
	MovementComp->Velocity = FVector(1.f, 0, 0);
	MovementComp->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;
}

void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();
	if (DamagePolicy == EProjectileMovementMode::OnBeginOverlap)
	{
		CollisionBoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
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
	if (const bool bIsPlayerBlocking = UFunctionLibrary_Base::NativeDoesActorHaveTag(HitPawn, GameplayTags_Base::Player_Status_Blocking))
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
		HandleApplyProjectileDamage(HitPawn, EventData);
	}
	Destroy();
}

void AProjectile_Base::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor))
		return;

	OverlappedActors.AddUnique(OtherActor);

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UFunctionLibrary_Base::IsTargetPawnHostile(GetInstigator(), HitPawn))
		{
			FGameplayEventData EventData;
			EventData.Instigator = GetInstigator();
			EventData.Target = HitPawn;
			HandleApplyProjectileDamage(HitPawn, EventData);
		}
	}
}

void AProjectile_Base::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayLoad)
{
	checkf(DamageEffectSpecHandle.IsValid(), TEXT("Forget to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());

	// ? why const
	if (const bool bWasApplied = UFunctionLibrary_Base::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, DamageEffectSpecHandle))
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(InHitPawn, GameplayTags_Base::Shared_Event_HitReact, InPayLoad);
	}
}
