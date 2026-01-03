#include "AbilitySystem/Abilities/GameplayAbility_Player.h"

#include "GameplayTags_Base.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "Characters/Character_Player.h"
#include "Controllers/PlayerController_Base.h"

ACharacter_Player* UGameplayAbility_Player::GetPlayerCharacterFromActorInfo()
{
	if(!CachedPlayer.IsValid())
	{
		CachedPlayer = Cast<ACharacter_Player>(CurrentActorInfo->AvatarActor);
	}
	return CachedPlayer.IsValid() ? CachedPlayer.Get() : nullptr;
}

APlayerController_Base* UGameplayAbility_Player::GetPlayerControllerFromActorInfo()
{
	if(!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<APlayerController_Base>(CurrentActorInfo->PlayerController);
	}
	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UCombatComponent_Player* UGameplayAbility_Player::GetPlayerCombatCompFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComp();
}

UUIComponent_Player* UGameplayAbility_Player::GetPlayerUICompFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerUIComponent();
}

FGameplayEffectSpecHandle UGameplayAbility_Player::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemCompFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle Handle = GetAbilitySystemCompFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	Handle.Data->SetSetByCallerMagnitude(GameplayTags_Base::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	if(InCurrentAttackTypeTag.IsValid())
	{
		Handle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	return Handle;
}

// ?
bool UGameplayAbility_Player::GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime)
{
	check(InCooldownTag.IsValid());
	FGameplayEffectQuery        CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());
	TArray<TPair<float, float>> TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);
	if(!TimeRemainingAndDuration.IsEmpty())
	{
		RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
		TotalCooldownTime = TimeRemainingAndDuration[0].Value;
	}
	return RemainingCooldownTime > 0.f;
}
