// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Types/StructType_Base.h"
#include "AbilitySystemComponent_Base.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UAbilitySystemComponent_Base : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "Character|Ability", meta = (ApplyLevel="1"))
	void GrantWeaponAbilities(const TArray<FAbilitySet_Player>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);
};
