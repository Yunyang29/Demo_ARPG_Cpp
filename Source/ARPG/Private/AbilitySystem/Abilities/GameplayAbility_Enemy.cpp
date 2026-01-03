#include "AbilitySystem/Abilities/GameplayAbility_Enemy.h"

#include "GameplayTags_Base.h"
#include "Characters/Character_Enemy.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"

ACharacter_Enemy* UGameplayAbility_Enemy::GetEnemyCharacterFromActorInfo()
{
	if(!CachedEnemy.IsValid())
	{
		CachedEnemy = Cast<ACharacter_Enemy>(CurrentActorInfo->AvatarActor);
	}
	return CachedEnemy.IsValid() ? CachedEnemy.Get() : nullptr;
}

UCombatComponent_Enemy* UGameplayAbility_Enemy::GetEnemyCombatCompFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComp();
}

FGameplayEffectSpecHandle UGameplayAbility_Enemy::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemCompFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle Handle = GetAbilitySystemCompFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	Handle.Data->SetSetByCallerMagnitude(GameplayTags_Base::Shared_SetByCaller_BaseDamage, InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));

	return Handle;
}
