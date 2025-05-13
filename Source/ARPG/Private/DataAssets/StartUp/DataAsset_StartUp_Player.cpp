#include "DataAssets/StartUp/DataAsset_StartUp_Player.h"

#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "AbilitySystem/Abilities/GameplayAbility_Player.h"

bool FAbilitySet_Player::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UDataAsset_StartUp_Player::GiveToAbilitySystemComponent(UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for(const FAbilitySet_Player& AbilitySet : StartUpAbilitySets)
	{
		if(!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag); // 这里的DynamicAbilityTags是一个GameplayTagContainer，用于存储动态的能力标签
		// AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
