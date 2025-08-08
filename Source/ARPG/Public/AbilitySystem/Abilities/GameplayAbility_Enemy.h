#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbility_Base.h"
#include "Components/Combat/CombatComponent_Enemy.h"
#include "GameplayAbility_Enemy.generated.h"

class ACharacter_Enemy;

/**
 * 
 */
UCLASS()
class ARPG_API UGameplayAbility_Enemy : public UGameplayAbility_Base
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "A_My|Enemy|Ability")
	ACharacter_Enemy* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "A_My|Enemy|Ability")
	UCombatComponent_Enemy* GetEnemyCombatCompFromActorInfo();

private:
	TWeakObjectPtr<ACharacter_Enemy> CachedEnemy;
};
