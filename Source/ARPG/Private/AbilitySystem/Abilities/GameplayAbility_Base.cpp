#include "AbilitySystem/Abilities/GameplayAbility_Base.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "Components/Combat/CombatComponent_Base.h"

/// @brief
/// @param ActorInfo
/// @param Spec
void UGameplayAbility_Base::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if(AbilityActivationPolicy == EAbilityActivationPolicy_Base::OnGiven)
	{
		if(ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

/// @brief
/// @param Handle
/// @param ActorInfo
/// @param ActivationInfo
/// @param bReplicateEndAbility
/// @param bWasCancelled
void UGameplayAbility_Base::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if(AbilityActivationPolicy == EAbilityActivationPolicy_Base::OnGiven)
	{
		if(ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

/// @brief
/// @return
UCombatComponent_Base* UGameplayAbility_Base::GetPawnCombatCompFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UCombatComponent_Base>();
}

/// @brief
/// @return
UAbilitySystemComponent_Base* UGameplayAbility_Base::GetAbilitySystemCompFromActorInfo() const
{
	return Cast<UAbilitySystemComponent_Base>(CurrentActorInfo->AbilitySystemComponent);
}
