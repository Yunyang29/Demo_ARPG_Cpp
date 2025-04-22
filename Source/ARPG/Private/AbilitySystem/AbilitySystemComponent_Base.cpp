#include "AbilitySystem/AbilitySystemComponent_Base.h"

void UAbilitySystemComponent_Base::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid())
	{
		return;
	}

	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UAbilitySystemComponent_Base::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}
