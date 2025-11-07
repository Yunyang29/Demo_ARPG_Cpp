#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbility_Player.h"
#include "GameplayAbility_PickUpStones.generated.h"

class AStone_Base;
/**
 * 
 */
UCLASS()
class ARPG_API UGameplayAbility_PickUpStones : public UGameplayAbility_Player
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void CollectStone();
	
	UFUNCTION(BlueprintCallable)
	void ConsumeStones();

private:
	UPROPERTY(EditDefaultsOnly)
	float TraceDistance = 50.f;

	UPROPERTY(EditDefaultsOnly)
	FVector TraceSize = FVector(100.f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceChannel;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawnPersistentDebugShape = false;

	UPROPERTY()
	TArray<AStone_Base*> CollectedStones;
};
