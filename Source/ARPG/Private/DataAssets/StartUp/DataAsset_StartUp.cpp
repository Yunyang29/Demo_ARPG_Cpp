
#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MainGameplayAbility.h"
#include "DebugHelper.h"

void UDataAsset_StartUp::GiveToAbilitySystemComponent(UMainAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartUp::GrantAbilities(const TArray<TSubclassOf<UMainGameplayAbility>>& InAbilitiesToGive, UMainAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UMainGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
