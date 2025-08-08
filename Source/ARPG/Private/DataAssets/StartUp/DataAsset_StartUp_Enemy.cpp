#include "DataAssets/StartUp/DataAsset_StartUp_Enemy.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"

void UDataAsset_StartUp_Enemy::GiveToAbilitySystemComponent(UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if(!EnemyCombatAbilities.IsEmpty())
	{
		for(const TSubclassOf<UGameplayAbility_Enemy>& AbilityClass : EnemyCombatAbilities)
		{
			if(!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
