#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitSpawnEnemies.generated.h"

class ACharacter_Enemy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<ACharacter_Enemy*>&, SpawnedEnemies);

/**
 * 
 */
UCLASS()
class ARPG_API UAbilityTask_WaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="A_My|AbilityTask",
		meta=(DisplayName = "Wait Gameplay Event and Spawn Enemeies",
			HidePin="OwningAbility",
			DefaultToSelf="OwningAbility",
			BlueprintInternalUseOnly="true",
			NumToSpawn = "1",
			RandomSpawnRadius ="200"
		))
	static UAbilityTask_WaitSpawnEnemies* WaitSpawnEnemies(
		UGameplayAbility* OwningAbility,
		FGameplayTag EventTag,
		TSoftClassPtr<ACharacter_Enemy> SoftEnemyClassToSpawn,
		int32 NumToSpawn,
		const FVector& SpawnOrigin,
		float RandomSpawnRadius,
		const FRotator& SpawnRotation
	);

	UPROPERTY(BlueprintAssignable, Category="A_My|AbilityTask")
	FWaitSpawnEnemiesDelegate OnSpawnFinished;

	UPROPERTY(BlueprintAssignable, Category="A_My|AbilityTask")
	FWaitSpawnEnemiesDelegate DidNotSpawn;

private:
	FGameplayTag CachedEventTag;
	TSoftClassPtr<ACharacter_Enemy> CachedSoftEnemyClassToSpawn;
	FVector CachedSpawnOrigin;
	int32 CachedNumToSpawn;
	FRotator CachedSpawnRotation;
};
