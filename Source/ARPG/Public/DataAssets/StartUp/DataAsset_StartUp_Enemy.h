#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbility_Enemy.h"
#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "DataAsset_StartUp_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UDataAsset_StartUp_Enemy : public UDataAsset_StartUp
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayAbility_Enemy>> EnemyCombatAbilities;
};
