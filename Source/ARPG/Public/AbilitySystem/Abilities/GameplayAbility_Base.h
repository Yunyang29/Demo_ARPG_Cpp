#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Base.generated.h"

class UCombatComponent_Base;
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
	
	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	UCombatComponent_Base* GetPawnCombatCompFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	UAbilitySystemComponent_Base* GetAbilitySystemCompFromActorInfo() const;
};
