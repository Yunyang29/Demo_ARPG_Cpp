#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/PickUp_Base.h"
#include "Stone_Base.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent_Base;
/**
 * 
 */
UCLASS()
class ARPG_API AStone_Base : public APickUp_Base
{
	GENERATED_BODY()

public:
	void Consume(UAbilitySystemComponent_Base* AbilitySystemComponent, int32 ApplyLevel);

protected:
	virtual void OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Do Stone Consumed"))
	void BP_OnStoneConsumed();


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
};
