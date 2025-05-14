#include "AbilitySystem/AbilitySystemComponent_Base.h"

#include "DebugHelper.h"
#include "AbilitySystem/Abilities/GameplayAbility_Player.h"

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

void UAbilitySystemComponent_Base::GrantWeaponAbilities(const TArray<FAbilitySet_Player>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if(InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for(const FAbilitySet_Player& AbilitySet : InDefaultWeaponAbilities)
	{
		if(!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UAbilitySystemComponent_Base::RemoveGrantedWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if(InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for(const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if(!SpecHandle.IsValid()) continue;

		ClearAbility(SpecHandle);
	}

	InSpecHandlesToRemove.Empty();
}
