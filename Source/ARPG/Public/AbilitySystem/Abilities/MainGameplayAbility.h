// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MainGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EMainAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class ARPG_API UMainGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool                             bWasCancelled) override;
	//~ End UGameplayAbility Interface.

	UPROPERTY(EditDefaultsOnly, Category = "MainAbility")
	EMainAbilityActivationPolicy AbilityActivationPolicy = EMainAbilityActivationPolicy::OnTriggered;
};
