#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Base.generated.h"

class UCombatComponent_Pawn;
class UAbilitySystemComponent_Base;


UENUM(BlueprintType)
enum class EAbilityActivationPolicy_Base : uint8
{
	OnTriggered,
	OnGiven
};

/**
 *
 */
UCLASS()
class ARPG_API UGameplayAbility_Base : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface.

	UPROPERTY(EditDefaultsOnly, Category = "MainAbility")
	EAbilityActivationPolicy_Base AbilityActivationPolicy = EAbilityActivationPolicy_Base::OnTriggered;
	
	UFUNCTION(BlueprintPure, Category = "Char|Ability")
	UCombatComponent_Pawn* GetPawnCombatCompFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Char|Ability")
	UAbilitySystemComponent_Base* GetASCompFromActorInfo() const;
};
