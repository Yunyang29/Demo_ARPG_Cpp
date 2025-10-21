#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameFramework/Actor.h"
#include "Projectile_Base.generated.h"

struct FGameplayEffectSpecHandle;
class UBoxComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;

UENUM(BlueprintType)
enum class EProjectileMovementMode : uint8
{
	OnHit,
	OnBeginOverlap,
};

UCLASS()
class ARPG_API AProjectile_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="A_MY|Projectile")
	UBoxComponent* CollisionBoxComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="A_MY|Projectile")
	UNiagaraComponent* NiagaraComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="A_MY|Projectile")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="A_MY|Projectile")
	EProjectileMovementMode DamagePolicy = EProjectileMovementMode::OnHit;

	UPROPERTY(BlueprintReadOnly, Category="A_MY|Projectile", meta=(ExposeOnSpawn="true"))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UFUNCTION()
	virtual void OnProjectHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, meta=(AdvancedDisplay="On Spawn Projectile Hit FX"))
	void BP_OnSpawnProjectileHitFX(const FVector& HitLocation);

private:
	void HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayLoad);

	TArray<AActor*> OverlappedActors;
};
