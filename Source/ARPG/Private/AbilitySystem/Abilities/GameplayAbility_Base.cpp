#include "AbilitySystem/Abilities/GameplayAbility_Base.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "Components/Combat/CombatComponent_Pawn.h"

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

UCombatComponent_Pawn* UGameplayAbility_Base::GetPawnCombatCompFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UCombatComponent_Pawn>();
}

UAbilitySystemComponent_Base* UGameplayAbility_Base::GetASCompFromActorInfo() const
{
	return Cast<UAbilitySystemComponent_Base>(CurrentActorInfo->AbilitySystemComponent);
}
