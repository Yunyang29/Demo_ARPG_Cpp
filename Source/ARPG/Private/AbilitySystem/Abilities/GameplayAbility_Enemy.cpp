#include "AbilitySystem/Abilities/GameplayAbility_Enemy.h"
#include "Characters/Character_Enemy.h"

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
