//#include "DataAssets/StartUpData/DataAsset_StartupDataBase.h"
//#include  "AbilitySystem/MainAbilitySystemComponent.h"
//#include  "AbilitySystem/Abilities/MainGameplayAbility.h"
//
//void UDataAsset_StartupDataBase::GiveToAbilitySystemComponent(UMainAbilitySystemComponent* InCharacterASCToGive, int32 ApplyLevel)
//{
//	check(InCharacterASCToGive);
//	GrantAbilities(ActivateOnGivenAbilities, InCharacterASCToGive, ApplyLevel);
//	GrantAbilities(ReactiveAbilities, InCharacterASCToGive, ApplyLevel);
//}
//
//void UDataAsset_StartupDataBase::GrantAbilities(const TArray<TSubclassOf<UMainGameplayAbility>>& InAbilitiesToGive, UMainAbilitySystemComponent* InCharacterASCToGive, int32 ApplyLevel)
//{
//	if (InAbilitiesToGive.IsEmpty())
//	{
//		return;
//	}
//
//	for (const TArray<TSubclassOf<UMainGameplayAbility>>& Ability : InAbilitiesToGive)
//	{
//		if (!Ability) continue;
//
//		FGameplayAbilitySpec AbilitySpec(Ability);
//		AbilitySpec.SourceObject = InCharacterASCToGive->GetAvatarActor();
//		AbilitySpec.Level = ApplyLevel;
//		InCharacterASCToGive->GiveAbility(AbilitySpec);
//	}
//}
