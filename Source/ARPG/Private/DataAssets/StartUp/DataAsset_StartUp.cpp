
#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "AbilitySystem/Abilities/GameplayAbility_Base.h"
#include "DebugHelper.h"

void UDataAsset_StartUp::GiveToAbilitySystemComponent(UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartUp::GrantAbilities(const TArray<TSubclassOf<UGameplayAbility_Base>>& InAbilitiesToGive, UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UGameplayAbility_Base>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
